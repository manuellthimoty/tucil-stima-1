let inputArr = []
let colorMap = new Map();
let sliderVal = 1000;
var n;

const textInput = document.getElementById("text-input");
const startButton = document.getElementById("start-button");
const grids = document.getElementById("grids");
const ansGrids = document.getElementById("answer-grids");
const statusId = document.getElementById("status");
const iter = document.getElementById("iter");
const totalTime = document.getElementById("time");
const toggleCheckBox = document.getElementById("toggle");
const stopButton = document.getElementById("stop-button");
const fileInput = document.getElementById("file_input");
const slider = document.getElementById("iter-slider");
const displaySlide = document.getElementById("iter-display");

let uniqueColor = new Set();

let method = "";
let evtSrc = null;
let inputValid = true;

let valid = true;
let found = true;
var finalResult;

let numIt = 0;
let time = 0;
let curPar = 0;

// pengatur value slider
slider.addEventListener("input",(e) => {
    displaySlide.innerText = "Every " + e.target.value + " iterations";
    sliderVal = e.target.value;
})


fileInput.addEventListener("change",(e) => {
    const file = e.target.files[0];
    if(!file) return;
    
    const reader = new FileReader();
    reader.onload = (e) => {
        const res = e.target.result;
        textInput.value = "";
        textInput.value = res;
    };
    reader.readAsText(file);

})

// ngecek apakah input hanya contain string
function isOnlyLetters(str) {
  return /^[a-zA-Z]+$/.test(str);
}

toggleCheckBox.addEventListener("change", (e) => {
    if(e.target.checked) {
        method = "optimize";
    } else {
        method = "naive";
    }
});

const setN = () => {
    let cur = 0;
    while(textInput.value[cur] !== '\n' && cur < textInput.value.length){
        cur++;
    }
    n = cur;
}

const parseInput = () => {
    inputValid = true;
    const text = textInput.value;
    valid = true;
    const lines = text.split('\n');
    if(lines.length !== n){
        valid = false;
        return;
    }
    for(let i = 0 ; i < n ; i++){
        if(lines[i].length !== n || !isOnlyLetters(lines[i])){
            valid = false;
            return;
        }
        inputArr[i] = [];
        for(let j = 0 ; j < n ; j++){
            inputArr[i][j] = lines[i][j];
            uniqueColor.add(inputArr[i][j]);
        }
    }
}
const setGrids = () => {
    grids.style.gridTemplateColumns = `repeat(${n}, minmax(0, 1fr))`;
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
    evtSrc = new EventSource(
        `http://localhost:3000/solve?input=${encodeURIComponent(textInput.value)}&n=${n}&method=${method}&slider=${sliderVal}`
    )
    
    evtSrc.onmessage = (event) => {
        try{
            const data = JSON.parse(event.data);
            let foundnum = false;
            if(data.progress) {
                acc += data.progress;
                let lines = acc.split('\n').filter(line => line.trim() !== '');
                if( n <= 3){
                    const curRes = lines.slice(-3);
                    let num1 = Number(curRes[0].trim());
                    let num2 = Number(curRes[1].trim());
                    let num3 = Number(curRes[2].trim());
                    if(!isNaN(num1) && !isNaN(num2)){
                        numIt = num1;
                        time = num2;
                        if(num3 == 1) found = true;
                        else found = false;

                    }
                    else{
                        console.log(curRes);
                        generateLiveGrid(curRes);
                    }
                }
                else if(lines.length >=n){

                    const curRes = lines.slice(-n);
                    let num1 = Number(curRes[n-3].trim());
                    let num2 = Number(curRes[n-2].trim());
                    let num3 = Number(curRes[n-1].trim());
                    if(!isNaN(num1) && !isNaN(num2)){
                        numIt = num1;
                        time = num2;
                        if(num3 == 1) found = true;
                        else found = false;

                    }
                    else{
                        console.log(curRes);
                        generateLiveGrid(curRes);
                    }
                }
            }
            if(data.success){
                if(!foundnum){
                    finalResult = data.result.split('\r\n').filter(line => line !== '');
                    finalResult = finalResult.slice(-n-3);
                    finalResult = finalResult.slice(0,n);
                    
                    generateGridAns();
                    generateQueenPos();
                    if(found){
                        statusId.innerText = "FOUND !";
                        statusId.style.color = "var(--color-green-200)";
                    }
                    else{
                        statusId.innerText = "NOT FOUND !";
                        statusId.style.color = "var(--color-red-200)";
                    }
                    iter.innerText = "Number of Iterations: " + numIt + " Iterations";
                    totalTime.innerText = "Total time taken : " + time + " ms";
                    evtSrc.close();
                }
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
    const existingImgs = document.querySelectorAll('#answer-grids img');
    existingImgs.forEach(img => img.remove());

    if(!found || !Array.isArray(curr) || curr.length === 0) return;

    if(curr && curr.length > 0){
        for(let i = 0 ; i < n ; i++){
            const curLine = curr[i];
            for(let j = 0 ; j < n ; j++){
                if(curLine[j] === "#"){
                    const elmtId = 'ans' + i + j;
                    const curElmt = document.getElementById(elmtId);
                    if(curElmt){
                        const oldimg = curElmt.querySelector('img');
                        if(oldimg) oldimg.remove();

                        const quennimg = document.createElement('img');
                        quennimg.src = "../assets/light.png";
                        curElmt.appendChild(quennimg);
                    }
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
                    quennimg.src = "../assets/light.png";
                    curElmt.appendChild(quennimg);
                }
            }
        }
    }
}
stopButton.addEventListener("click",()=> {
    if(evtSrc){
        evtSrc.close();
        evtSrc = null;
    }
})
let end = false;
startButton.addEventListener("click", (e) =>{
    uniqueColor.clear();
    found = true;
    e.preventDefault();
    if(evtSrc){
        evtSrc.close();
        evtSrc = null;
    }
    setN();
    parseInput();
    if(!valid){
        alert('Invalid Input');
    }
    else{
        setGrids();
        generateColorMap();
        if(uniqueColor.size !== n){
            alert("Banyak warna unik tidak sesuai");
            return;
        }
        generateGridAns();
        liveCalc();
        
    }

})