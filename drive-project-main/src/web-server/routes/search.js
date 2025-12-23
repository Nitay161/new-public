const express = require('express')
const router = express.Router()
const controller = require('../controllers/files')

router.route('/:query')
    .get(controller.searchByQuery)

module.exports = router