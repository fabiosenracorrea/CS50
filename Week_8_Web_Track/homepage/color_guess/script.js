let score = 0;
let level = 0;
let streak = 0;
let hardMode = Boolean(localStorage.getItem('hard-mode')) || false;
let lives = 3;
let highScore = localStorage.getItem('high-score') || 0;
let highestLevel = localStorage.getItem('high-level') || 0;
let highestStreak = localStorage.getItem('high-streak') || 0;

function generateColor() {
  const red = Math.floor(Math.random() * 255);
  const green = Math.floor(Math.random() * 255);
  const blue = Math.floor(Math.random() * 255);
  const rgb = `rgb(${red}, ${green}, ${blue})`;

  return rgb
}

function fillLevelColor() {
  const balls = document.querySelectorAll('.ball');
  const numberOfBalls = balls.length;

  const randBall = Math.floor(Math.random() * (numberOfBalls - 1));

  let color = window.getComputedStyle(balls[randBall]).getPropertyValue('background-color');
  color = color.replace('rgb', '');

  const display = document.getElementById('rgb-color');
  display.innerText = color;
}

function updateHighScore() {
  const highScoreElement = document.getElementById('high-score-container');
  const levelScoreElement = document.getElementById('level-score-container');
  const streakScoreElement = document.getElementById('streak-score-container');

  if (hardMode) {
    if (score > highScore) {
      highScore = score;
      localStorage.setItem('high-score', highScore);
    }

    if (level > highestLevel) {
      highestLevel = level;
      localStorage.setItem('high-level', level);
    }

    if (streak > highestStreak) {
      highestStreak = streak;
      localStorage.setItem('high-streak', streak);
    }

    highScoreElement.innerText = highScore;
    levelScoreElement.innerText = highestLevel;
    streakScoreElement.innerText - highestStreak;
  }
}

function loadHighScore() {
  const highScoreElement = document.getElementById('high-score-container');
  const levelScoreElement = document.getElementById('level-score-container');
  const streakScoreElement = document.getElementById('streak-score-container');


  highScoreElement.innerText = highScore;
  levelScoreElement.innerText = highestLevel;
  streakScoreElement.innerText - highestStreak;

}

function updateScore(hit) {
  if (hit) {
    if (hardMode) {
      score += 3 * streak;
    } else {
      score += 3;
    }

    const scoreElement = document.getElementById('score');
    scoreElement.innerText = score;

    level += 1;
    const levelElement = document.getElementById('level');
    levelElement.innerText = level;

    updateHighScore();
  } else {
    score = 0;
    const scoreElement = document.getElementById('score');
    scoreElement.innerText = score;
  }
}

function updateHardModeLives() {
  if (lives) {
    const hps = document.querySelectorAll('.hp');
    const currentLive = 'hp' + lives;
    hps[lives - 1].classList.add(currentLive);
    lives -= 1;
  }

  checkLives();
}

function showModal() {
  const modal = document.getElementById('modal');
  modal.classList.toggle('hide');
  const answer = document.getElementById('answer');


  setTimeout(() => {
    modal.classList.toggle('hide');
    answer.innerText = 'Escolha uma cor';
  }, 2000);
}

function checkLives() {
  if (!lives) {
    // show you lose modal
    showModal();
    // reset level
    level = 0;
    const levelElement = document.getElementById('level');
    levelElement.innerText = level;
    fillBalls();
    fillLevelColor();

    // reset score
    updateScore(false);

    // reset hp
    const hpContainer = document.querySelectorAll('.hp');
    for (let i = 1; i <= 3; i += 1) {
      const heartNumber = 'hp' + i
      hpContainer[i - 1].classList.remove(heartNumber);
    };

    lives = 3;
  }
}

function checkColor(event) {
  const display = document.getElementById('rgb-color');
  const color = 'rgb' + display.innerText;

  const answer = document.getElementById('answer');

  if (event.target.style.backgroundColor === color) {
    answer.innerText = 'Acertou!';
    streak += 1;
    updateScore(true);
    fillBalls();
    fillLevelColor();
  } else {
    streak = 1;
    answer.innerText = 'Errou! Tente novamente';
    if (hardMode) {
      updateHardModeLives();
    }
  }
}

function fillBalls() {
  const balls = document.querySelectorAll('.ball');

  balls.forEach((ball) => {
    rgb = generateColor();
    ball.style.backgroundColor = rgb;

    ball.addEventListener('click', checkColor)
  })
}

function disableHardMode() {
  hardMode = false;
  localStorage.setItem('hard-mode', '');
  const checkInput = document.getElementById('hard-mode-checker');
  checkInput.checked = false;
  checkInput.style.pointerEvents = 'all';

  const hpContainer = document.querySelector('.hp-container');
  const highScoreContainer = document.querySelector('.high-scores');

  hpContainer.classList.add('not-hard-mode');
  highScoreContainer.classList.add('not-hard-mode');
}

function enableButton() {
  const btn = document.querySelector('button');

  btn.onclick = () => {
    const answer = document.getElementById('answer');
    answer.innerText = 'Escolha uma cor';

    disableHardMode();

    fillBalls();
    fillLevelColor();

    level = 0;
    const levelElement = document.getElementById('level');
    levelElement.innerText = level;
  }
}

function loadHardMode() {
  hardMode = true;
  localStorage.setItem('hard-mode', '1');
  level = 0;
  score = 0;
  updateScore(false);
  fillBalls();
  fillLevelColor();
  const levelElement = document.getElementById('level');
  levelElement.innerText = level;
  const answer = document.getElementById('answer');
  answer.innerText = 'Escolha uma cor';
  const checkInput = document.getElementById('hard-mode-checker');
  checkInput.style.pointerEvents = 'none';

  const hpContainer = document.querySelector('.hp-container');
  const highScoreContainer = document.querySelector('.high-scores');

  hpContainer.classList.remove('not-hard-mode');
  highScoreContainer.classList.remove('not-hard-mode');
}

function checkHardMode() {
  const checkInput = document.getElementById('hard-mode-checker');
  if (hardMode) {
    checkInput.checked = true;
    loadHardMode();
  }
}


function enableHardMode() {
  const checkInput = document.getElementById('hard-mode-checker');

  checkInput.addEventListener('change', loadHardMode);
}

window.onload = () => {
  fillBalls();
  fillLevelColor();
  enableButton();
  checkHardMode();
  loadHighScore();
  enableHardMode();
}
