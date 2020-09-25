
let resized = false;

// --> desse jeito a mudança é mais devagar.
// window.onload = () => {
//   if (document.body.clientWidth < 685) {
//     sizeTableDown();
//   }
// }

if (document.body.clientWidth < 685) {
  sizeTableDown();
}


window.addEventListener("resize", event => {
  let width = document.body.clientWidth;
  if (width < 685 && !resized) {
    sizeTableDown()
  } else if (width > 685 && resized) {
    sizeTableUp()
  }
})


// functions

function sizeTableDown() {
  let table = document.getElementById("table");

  let headers = document.querySelectorAll("#table-header th");
  let descriptions = document.querySelectorAll("#table-info td");

  let newTr1 = document.createElement("tr");
  newTr1.setAttribute("id", "tr1")
  let newTr2 = document.createElement("tr");
  newTr2.setAttribute("id", "tr2")

  for (let i = 3; i < 6; i += 1) {
    let headerText = headers[i].outerText;
    let descText = descriptions[i].outerText;

    let tableHeaderTr = document.getElementById("table-header");
    let tableDescTr = document.getElementById("table-info");

    tableHeaderTr.removeChild(tableHeaderTr.lastElementChild);
    tableDescTr.removeChild(tableDescTr.lastElementChild);

    let newTh = document.createElement("th");
    let newTd = document.createElement("td");

    newTh.appendChild(document.createTextNode(headerText))

    if (i === 5) {
      let strongEl = document.createElement("strong");
      strongEl.appendChild(document.createTextNode(descText));
      newTd.appendChild(strongEl)
    } else {
      newTd.appendChild(document.createTextNode(descText));
    }

    newTr1.appendChild(newTh);
    newTr2.appendChild(newTd);
  }

  table.appendChild(newTr1);
  table.appendChild(newTr2);
  resized = true;
}

function sizeTableUp() {
  let tr1 = document.getElementById("tr1");
  let tr2 = document.getElementById("tr2");
  let tr1Size = tr1.children.length;
  let tr2Size = tr2.children.length;

  let tableHeaderTr = document.getElementById("table-header");
  let tableDescTr = document.getElementById("table-info");

  /* Sobre a peculiaridade abaixo: a cada vez que apendamos o 'filho' do tr1 em outro elemento, ele
  é MOVIDO para o novo local. Ou seja, não cria-se uma cópia. Por esse motivo, quando passamos pra segunda interação
  o tamanho do array de filhos é MENOR em 1 unidade. Logo, o nosso i sendo restrido pelo .length dinamico (sem ser uma variavel constante fora do for)
  gera um problema quanto ao remanejo dos filhos. Como queremos sempre na ordem, basta settarmos o loop para rodar pelo número fixo
  que é o tamanho inicial do elemento e sempre apendar o primeiro elemento do array!!
  */

  for (i = 0; i < tr1Size; i += 1) {
    tableHeaderTr.appendChild(tr1.children[0])
  }
  for (i = 0; i < tr2Size; i += 1) {
    tableDescTr.appendChild(tr2.children[0])
  }


  tr1.remove();
  tr2.remove();

  resized = false;
}
