const { hasPermissions } = require('../models/files')
const { isExist } = require('../models/files')
const File = require('../models/files')

exports.getAllFiles = (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))
    res.json(File.getAllFiles(userId))
}

exports.createFile = async (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))
    // getting title, content and type (file or folder) for the file.
    const { title, content, type } = req.body
    if (!type) return res.status(400).json({ error: 'Type required' })
    

    if (type == "file" && (!title || !content))
        return res.status(400).json({ error: 'Title and content required' })

    if (type == "folder" && (!title || content))
        return res.status(400).json({ error: 'Only title required for folders' })

    try {
        const newFile = await File.createFile(title, content, type, userId)
        res.status(201).location(`/api/files/${newFile.id}`).end()

    } catch (err) {
        return res.status(err.status).json({ error: err.message })
    }
}

exports.getFileById = async (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))

    // getting file by sending the id and the user id.
    const fileId = parseInt(req.params.id)
    if (!File.isExist(fileId))
        return res.status(404).json({ error: 'File not found' })

    // if does not have read permissions.
    if (!File.hasPermissions(fileId, userId, 1))
        return res.status(400).json({ error: 'You dont have read permissions for this file' })

    const type = File.isFolder(fileId) ? "folder" : "file"
    
    if (!(type == "file" || type == "folder"))
        return res.status(400).json({ error: 'Type can be only file or folder' })

    try {
        const file = await File.getFile(fileId)
        res.status(200).json(file)
    } catch (err) {
        return res.status(err.status).json({ error: err.message })
    }
}

exports.updateFile = async (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))

    // getting new file title and content.
    const { title, content } = req.body

    // getting file id.
    const fileId = parseInt(req.params.id)
    if (!File.isExist(fileId))
        return res.status(404).json({ error: 'File not found' })
    if (File.isFolder(fileId) && content)
        return res.status(400).json({ error: 'No content is required for folders' })
    // if does not have write permissions.
    if (!File.hasPermissions(fileId, userId, 2))
        return res.status(400).json({ error: 'You dont have write permissions for this file' })

    // if no title and content provided.
    if (!title || !content)
        return res.status(400).json({ error: 'Title and content required' })
    
    try {
        const file = await File.updateFile(fileId, title, content)
        res.status(204).end()
    } catch (err) {
        return res.status(err.status).json({ error: err.message })
    }
}

exports.deleteFile = async (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))
    // getting file id.
    const fileId = parseInt(req.params.id)
    if (!File.isExist(fileId))
        return res.status(404).json({ error: 'File not found' })
    // if does not have delete permissions.
    if (!File.hasPermissions(fileId, userId, 4))
        return res.status(400).json({ error: 'You dont have delete permissions for this file' })

    try {
        await File.deleteFile(fileId)
        res.status(204).end()
    } catch (err) {
        return res.status(err.status).json({ error: err.message })
    }
}

exports.getPermissionsById = (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))
    // getting file id.
    const fileId = parseInt(req.params.id)
    if (!File.isExist(fileId))
        return res.status(404).json({ error: 'File not found' })
    // if is not the creator.
    if (!File.isCreator(fileId, userId))
        return res.status(400).json({ error: 'Only file creator can access permissions' })

    res.status(200).json(File.getFilePermissions(fileId))
}

exports.createPermissions = (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))
    // getting file id.
    const fileId = parseInt(req.params.id)
    if (!File.isExist(fileId))
        return res.status(404).json({ error: 'File not found' })
    // if is not the creator.
    if (!File.isCreator(fileId, userId))
        return res.status(400).json({ error: 'Only file creator can access permissions' })

    const { pid, perms } = req.body
    if (!pid || !perms)
        return res.status(400).json({ error: 'No pid or permissions provided' })
    if (perms < 0 || perms > 7)
        return res.status(400).json({ error: 'Permissions can be only between 0-7' })
    File.createFilePermissions(fileId, pid, perms)
    res.status(201).end()
}

exports.updatePermissions = (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))
    // getting file id.
    const fileId = parseInt(req.params.id)
    // getting file pid.
    const pid = parseInt(req.params.pId)
    if (!File.isExist(fileId))
        return res.status(404).json({ error: 'File not found' })
    // if is not the creator.
    if (!File.isCreator(fileId, userId))
        return res.status(400).json({ error: 'Only file creator can access permissions' })

    const { perms } = req.body
    if (!perms)
        return res.status(400).json({ error: 'No permissions provided' })
    if (perms < 0 || perms > 7)
        return res.status(400).json({ error: 'Permissions can be only between 0-7' })
    File.updateFilePermissions(fileId, pid, perms)
    res.status(204).end()
}

exports.deletePermissions = (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))
    // getting file id.
    const fileId = parseInt(req.params.id)
    // getting file pid.
    const pid = parseInt(req.params.pId)
    if (!File.isExist(fileId))
        return res.status(404).json({ error: 'File not found' })
    // if is not the creator.
    if (!File.isCreator(fileId, userId))
        return res.status(400).json({ error: 'Only file creator can access permissions' })

    File.deleteFilePermissions(fileId, pid)
    res.status(204).end()
}

exports.searchByQuery = async (req, res) => {
    // getting user id from http header.
    const userId = parseInt(req.get("User-Id"))
    // getting the query.
    const query = req.params.query

    try {
        const results = await File.searchByQuery(query, userId)
        res.status(200).json(results)
    } catch (err) {
        return res.status(err.status).json({ error: err.message })
    }
}