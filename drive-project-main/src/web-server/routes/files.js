const express = require('express')
const router = express.Router()
const controller = require('../controllers/files')

router.route('/')
    .get(controller.getAllFiles)
    .post(controller.createFile)

router.route('/:id')
    .get(controller.getFileById)
    .patch(controller.updateFile)
    .delete(controller.deleteFile)

router.route('/:id/permissions')
    .get(controller.getPermissionsById)
    .post(controller.createPermissions)

router.route('/:id/permissions/:pId')
    .patch(controller.updatePermissions)
    .delete(controller.deletePermissions)

module.exports = router