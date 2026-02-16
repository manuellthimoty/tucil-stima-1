let inputArr = []
let colorMap = new Map();
var n;

const textInput = document.getElementById("text-input");
const startButton = document.getElementById("start-button");
const grids = document.getElementById("grids");
const ansGrids = document.getElementById("answer-grids");

let valid = true;
let found = true;
var finalResult;
const setN = () => {
    let cur = 0;
    while(textInput.value[cur] !== '\n' && cur < textInput.value.length){
        cur++;
    }
    n = cur;
}

const parseInput = () => {
    const text = textInput.value;
    let curcheck = 0;
    
    for(let i = 0; i < n; i++){
        inputArr[i] = [];
        for(let j = 0; j < n; j++){
            inputArr[i][j] = text[curcheck];
            curcheck++;
        }
        if(i < n - 1 && text[curcheck] !== '\n'){
            valid = false;
            break;
        }
        curcheck++; // skip newline character
    }
}
const setGrids = () => {
    grids.style.gridTemplateColumns = `repeat(${n}, minmax(0, 1fr))`;
}
const printInput = (arr) =>{
    for(let i = 0 ; i < arr.length ; i++){
        for(let j = 0 ; j < arr[0].length ; j++){
            console.log(arr[i][j]);
        }
    }
}

const generateColorMap = () => {
    for(let i = 0; i < n; i++){
        for(let j = 0; j < n; j++){
            if (!colorMap.has(inputArr[i][j])){
                let randomR = Math.floor(Math.random() * 256);
                let randomG = Math.floor(Math.random() * 256);
                let randomB = Math.floor(Math.random() * 256);
                let newColor = `rgb(${randomR}, ${randomG}, ${randomB})`;
                colorMap.set(inputArr[i][j], newColor);
            }
        }
    }
}

const generateGrid = () =>{
    grids.innerHTML = ""
    for(let i = 0 ; i < n ; i++){
        for(let j = 0 ; j < n ; j++){
            const newElmt = document.createElement("div");
            newElmt.className = "border aspect-square";
            newElmt.style.backgroundColor = colorMap.get(inputArr[i][j]);
            grids.appendChild(newElmt);
        }
    }
}

async function sendInput() {
    const res = await fetch("http://localhost:3000/solve",{
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({input: textInput.value, n : n})
    })

    const data = await res.json();
    if(data.success) {
        console.log("AMAN!");
        console.log("Hasil : " + data.result);
        finalResult = data.result.split('\r\n').filter(line => line !== '');
    }
    else{
        console.log("BELOM AMAN!");
        console.error("ERROR : ",data.error)
    }
}

function liveCalc(){
    let acc = "";
    const evtSrc = new EventSource(
        `http://localhost:3000/solve?input=${encodeURIComponent(textInput.value)}&n=${n}`
    )
    evtSrc.onmessage = (event) => {
        try{
            const data = JSON.parse(event.data);
            if(data.progress) {
                // Update live grid setiap iterasi - hanya hapus queens, jangan regenerate
                acc += data.progress;
                let lines = acc.split('\n').filter(line => line.trim() !== '');
                if(lines.length >=n){
                    const curRes = lines.slice(-n);
                    console.log(curRes);
                    generateLiveGrid(curRes);
                }
            }
            if(data.success){
                finalResult = data.result.split('\r\n').filter(line => line !== '');
                finalResult = finalResult.slice(-n);
                generateGridAns();
                generateQueenPos();
                evtSrc.close();
            }
            else if(data.error){
                console.timeLog('blom aman');
                evtSrc.close();
            }
        }
        catch (e){
            console.error(e);
        }
    }

    evtSrc.onerror = (event) => {
        console.error(event);
        evtSrc.close();
    }
}

const generateLiveGrid = (curr) => {
    document.querySelectorAll('#answer-grids img').forEach(img => img.remove());
    if(curr && curr.length > 0){
        for(let i = 0 ; i < n ; i++){
                for(let j = 0 ; j < n ; j++){
                    if(curr[i][j] == "#"){
                        let curElmt = document.getElementById('ans' + (i) + j);
                        let quennimg = document.createElement('img');
                        quennimg.src = "light.png";
                        curElmt.appendChild(quennimg);
                    }
                }
            }
        }
    }

const generateGridAns = () => {
    if (found){
        ansGrids.innerHTML = "";
        ansGrids.style.gridTemplateColumns = `repeat(${n}, minmax(0, 1fr))`;
        for(let i = 0; i < n; i++){
            for(let j = 0; j < n; j++){
                const newAnsElmt = document.createElement("div");
                newAnsElmt.id = 'ans' + (i) + j;
                newAnsElmt.className = "border aspect-square";
                newAnsElmt.style.backgroundColor = colorMap.get(inputArr[i][j]);
                ansGrids.appendChild(newAnsElmt);
            }
        }
    }
}

const generateQueenPos = () => {
    if(found && finalResult) {
        
        for(let i = 0 ; i < finalResult.length ; i++){
            for(let j = 0 ; j < n ; j++){
                if(finalResult[i][j] == "#"){
                    let curElmt = document.getElementById('ans' + (i) + j);
                    let quennimg = document.createElement('img');
                    quennimg.src = "light.png";
                    curElmt.appendChild(quennimg);
                }
            }
        }
    }
}

startButton.addEventListener("click", (e) =>{
    e.preventDefault();
    setN();
    parseInput();
    setGrids();
    generateColorMap();
    generateGrid();
    // await sendInput();
    generateGridAns();
    liveCalc();
    // generateQueenPos();
})