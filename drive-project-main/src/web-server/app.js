const express = require('express')
const app = express()
const fileRoutes = require('./routes/files');
const searchRoutes = require('./routes/search');

app.use(express.json())
app.use('/api/files', fileRoutes);
app.use('/api/search', searchRoutes);

app.listen(3000)