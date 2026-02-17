const { spawn } = require('node:child_process');
const path = require('path');
const express = require("express");
const cors = require("cors");
const app = express();
app.use(express.json());
app.use(cors());
app.get("/solve",(req,res) =>{
    const { input, n, method} = req.query;
    res.setHeader('Content-Type', 'text/event-stream');
    res.setHeader('Cache-Control', 'no-cache');
    res.setHeader('Connection', 'keep-alive');
    res.setHeader('Access-Control-Allow-Origin', '*');
    let exepath;
    if(method === 'optimize') {
        exepath = path.join(__dirname, '../bin/optimize.exe');
        } 
    else {
            exepath = path.join(__dirname, '../bin/naive.exe');
        }
    
    let childProcess;
    childProcess = spawn(exepath);
    // const childProcess = spawn('./pure-bruteforce.exe');1

    let output = "";
    let err = "";
    let lastSentLength = 0;

    childProcess.stdin.write(n + "\n" + input);
    childProcess.stdin.end();

    childProcess.stdout.on('data', (data) => {
        output += data.toString();
        const newdata = output.substring(lastSentLength);
        if(newdata.length > 0) {
            res.write(`data: ${JSON.stringify({ progress: newdata })}\n\n`);
            lastSentLength = output.length;
        }
        
    });

    childProcess.stderr.on('data',(data) => {
        err += data.toString();
    });

    childProcess.on('close', (c) => {
        if (c == 0) {
            res.write(`data: ${JSON.stringify({ success: true, result: output })}\n\n`);
        }
        else {
            res.write(`data: ${JSON.stringify({ success: false, error: err })}\n\n`);
        }
        res.end();
    });
})

const PORT = 3000;

app.listen(PORT, () => {
    console.log("Server http://localhost:3000")
})