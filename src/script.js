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

const generateGridAns = () => {
    if (found){
        ansGrids.innerHTML = "";
        ansGrids.style.gridTemplateColumns = `repeat(${n}, minmax(0, 1fr))`;
        for(let i = 0; i < n; i++){
            for(let j = 0; j < n; j++){
                const newAnsElmt = document.createElement("div");
                newAnsElmt.id = 'ans' + i + j;
                newAnsElmt.className = "border aspect-square";
                newAnsElmt.style.backgroundColor = colorMap.get(inputArr[i][j]);
                ansGrids.appendChild(newAnsElmt);
            }
        }
    }
}

const generateQueenPos = () => {
    if(found) {
        for(let i = 1 ; i <= n ; i++){
            for(let j = 0 ; j < n ; j++){
                if(finalResult[i][j] == "#"){
                    let curElmt = document.getElementById('ans' + (i-1) + j);
                    let quennimg = document.createElement('img');
                    quennimg.src = "light.png";
                    curElmt.appendChild(quennimg);
                }
            }
        }
    }
}

startButton.addEventListener("click",async (e) =>{
    e.preventDefault();
    setN();
    parseInput();
    setGrids();
    generateColorMap();
    generateGrid();
    await sendInput();
    generateGridAns();
    generateQueenPos();
})