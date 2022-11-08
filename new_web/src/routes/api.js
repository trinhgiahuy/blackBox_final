const express = require('express');
const router = express.Router();
const db = require('../db/db');

const sql= `SELECT name, dateUploaded, lat, lng, speed 
                FROM mydb 
                WHERE dateUploaded IN (
                    SELECT MAX(dateUploaded)
                    FROM mydb 
                    WHERE dateUploaded In( 
                        SELECT MAX(dateUploaded)
                        FROM mydb
                    )
                    GROUP BY name)`;

router.get('/', async function(req, res, next){
    res.json("Main page");

})

router.get('/overview', async function(req, res, next){
    res.json("Overview");
})

router.get('/management', async function(req, res, next){
    res.json("Management");
})

router.get('/map', async function(req, res, next){
    try{
        await db.makeQuery(sql, result => {
            res.json(result);
        })
    } 
    catch(err){
        console.log(err);
    }
})

module.exports = router;