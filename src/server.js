const { spawn,exec } = require('node:child_process');
const express = require("express");
const cors = require("cors");
const app = express();
app.use(express.json());
app.use(cors());
app.post("/solve",(req,res) =>{
    const { input, n} = req.body;
    const childProcess = spawn('./backtrack.exe');

    let output = "";
    let err = "";

    childProcess.stdin.write(n + "\n" + input);
    childProcess.stdin.end();

    childProcess.stdout.on('data', (data) => {
        output += data.toString();
    });

    childProcess.stderr.on('data',(data) => {
        err += data.toString();
    });

    childProcess.on('close', (c) => {
        if (c == 0) res.json({
            success : true,
            result: output
        });
        else res.json({
            success : false,
            error : err
        });
    });
})

const PORT = 3000;

app.listen(PORT, () => {
    console.log("Server http://localhost:3000")
})