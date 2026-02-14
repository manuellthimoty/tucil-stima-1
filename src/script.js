let inputArr = []
let colorMap = new Map();
const n = 9;

const textInput = document.getElementById("text-input");
const startButton = document.getElementById("start-button");
const grids = document.getElementById("grids");
grids.style.gridTemplateColumns = `repeat(${n}, minmax(0, 1fr))`;

const parseInput = () => {
    const text = textInput.value;
    let curcheck = 0;
    
    for(let i = 0; i < n; i++){
        inputArr[i] = [];
        for(let j = 0; j < n; j++){
            inputArr[i][j] = text[curcheck];
            curcheck++;
        }
        curcheck++; // skip newline character
    }
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

startButton.addEventListener("click",(e) =>{
    e.preventDefault;
    parseInput();
    generateColorMap();
    generateGrid();
})