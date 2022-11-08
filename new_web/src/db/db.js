const Connection = require('tedious').Connection;
const Request = require('tedious').Request;
const { TYPES } = require('tedious');
const dotenv = require('dotenv');
dotenv.config();

//SELECT  dateUploaded FROM mydb WHERE dateUploaded IN (SELECT MAX(dateUploaded FROM mydb GROUP BY name))

const config = {
    server: process.env.SERVER,
    authentication: {
        type: 'default',
        options: {
            userName: process.env.DB_USERNAME,
            password: process.env.DB_PASSWORD
        }
    },
    options: {
        encrypt: false,
        database: 'testdb',
        trustServerCertificate: true
    }
}

const connection = new Connection(config);

connection.on('connect', (err) => {
    if(err){
        console.log(err);
    }
});

connection.connect();

async function makeQuery(sql, callback){

    const request = new Request(sql, (err, rowCount) => {
        if (err) {
            console.log(err);
            return;
        } 
    })

    data = [];
    request.on('row', async (columns) => {
        var item = {};
        for (var name in columns){
            item[columns[name].metadata.colName] = columns[name].value;
        }
        data.push(item);
    })

    request.on("doneInProc", async (rowCount, more ,rows) => {
        await callback(data);
    })

    // request.on('requestCompleted', async () => {
    //     connection.close();
    // });

    connection.execSql(request);
}

module.exports = {makeQuery};