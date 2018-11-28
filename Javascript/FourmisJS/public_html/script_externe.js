var can = document.getElementById("grille");
var ctx = can.getContext('2d');
can.width = 401;
can.height = 401;
var tCase = 20;
var fourmis = [];
var baseF = new base();
var tas = [];


var phero = 20;
var nbFourmis = 5;
var vitesse = 100;

var matrice = new Array();

for(var a=0; a<401; a=a+20){
	for(var b=0; b<401; b=b+20){
		if (!matrice[a]) matrice[a] = new Array();
		matrice[a][b] = 0;
	}
}

//lignes, colonnes, base
ctx.beginPath();
ctx.fillStyle='#000000';
ctx.moveTo(0, 0);
var i = 0;
while (i < can.height) {
    ctx.lineTo(i, can.height);
    ctx.fill();
    i = i + tCase;
    ctx.moveTo(i, 0);
}
ctx.moveTo(0, 0);
var j = 0;
while (j < can.width) {
    ctx.lineTo(can.width, j);
    ctx.fill();
    j = j + tCase;
    ctx.moveTo(0, j);

}
dessinerBase(baseF);

//base de retour des fourmis
function base() {
    this.x = (can.height / 2) - 0.5;
    this.y = (can.width / 2) - 0.5;
    this.dessinerBase = dessinerBase;

}

function dessinerBase(base) {
	ctx.fillStyle = '#000000';
    ctx.beginPath();
    ctx.arc(base.x+10, base.y+10, 10, 0, 2 * Math.PI);
    ctx.fill();
	//ctx.fillRect(base.x, base.y, 20, 20);
}

function expipheromones() {
	for(var a=0; a<401; a=a+20){
		for(var b=0; b<401; b=b+20){
			if(matrice[a][b]>0){
				matrice[a][b]=matrice[a][b]-1;
				ctx.fillStyle='#00FFFF';
				ctx.fillRect(a,b,a+20,b+20);
				ctx.strokeRect(a,b,a+20,b+20);
			} else {
				ctx.fillStyle='#FFFFFF';
				ctx.fillRect(a,b,a+20,b+20);
				ctx.strokeRect(a,b,a+20,b+20);
			}
		}
	}
}

//Tas de nourritures
function tasNour(x, y, taille) {
    this.x = x;
    this.y = y;
    this.taille = taille;
    this.dessinerTas = dessinerTas;
    this.diminuer = diminuer;
}

function dessinerTas() {
	ctx.fillStyle = '#FF6600';
	for(var z = 0; z<tas.length; z++){
		ctx.beginPath();
		ctx.arc(tas[z].x+10, tas[z].y+10, tas[z].taille, 0, 2 * Math.PI);
		ctx.fill();
	}
}

function diminuer(tas) {
    ctx.beginPath();
    ctx.fillStyle = '#FFFFFF';
    ctx.arc(tas.x+10, tas.y+10, tas.taille, 0, 2 * Math.PI);
    tas.taille = tas.taille - 1;
}

//Creation des tas
tas[0] = new tasNour(20, 20, 20);
tas[1] = new tasNour(260, 100, 5);
tas[2] = new tasNour(100, 300, 15);
tas[3] = new tasNour(360, 360, 10);
dessinerTas();

//Creation des fourmis
ctx.fillStyle = '#0000FF';
for (var i = 0; i < nbFourmis; i++) {
    fourmis[i] = new fourmi();
    fourmis[i].initFourmi();
}

//objet fourmi
function fourmi() {
    this.transporte = false;
    this.y = (can.height / 2) - 0.5;
    this.x = (can.width / 2) - 0.5;
    this.bouger = bouger;
    this.initFourmi = initFourmi;
}

function bouger(fmi, suivX, suivY) {
    ctx.beginPath();
	if((fmi.transporte)||(matrice[fmi.x][fmi.y]>0)){
		ctx.fillStyle = '#00FFFF';
		if(fmi.transporte){
			matrice[fmi.x][fmi.y] = phero;
		}
	} else {
		ctx.fillStyle = '#FFFFFF';
	}
    ctx.fillRect(fmi.x, fmi.y, 20, 20);
    ctx.strokeRect(fmi.x, fmi.y, 20, 20);
	if(fmi.transporte){
		ctx.fillStyle = '#FF0000';
	} else {
		ctx.fillStyle = '#0000FF';
	}
    ctx.fillRect(suivX, suivY, 20, 20);
    ctx.strokeRect(suivX, suivY, 20, 20);
    fmi.x = suivX;
    fmi.y = suivY;
	for(var i=0; i<tas.length; i++){
		tas[i].dessinerTas;
	}
}

//met la fourmi sur la base
function initFourmi() {
    ctx.fillRect(can.height / 2, can.width / 2, 20, 20);
}

//test si la fourmi est dans la grille
function dansLaGrille(x, y) {
    if ((x + 20) >= can.width || x < 0 || (y + 20) >= can.height || y < 0) {
        return false;
    }
    return true;
}

//animation
function loadGrille() {
    var tabXY = [0, tCase, -tCase];
	expipheromones();
    for (var i = 0; i < fourmis.length; i++) {
        var newX = 0;
        var newY = 0;
        if (fourmis[i].transporte) {
			var pheromin = 10;
            if (fourmis[i].x > baseF.x) {
                newX = fourmis[i].x - 20;
            } else if (fourmis[i].x < baseF.x) {
                newX = fourmis[i].x + 20;
            } else {
                newX = fourmis[i].x;
            }
            if (fourmis[i].y > baseF.y) {
                newY = fourmis[i].y - 20;
            } else if (fourmis[i].y < baseF.y) {
                newY = fourmis[i].y + 20;
            } else {
                newY = fourmis[i].y;
            }
            if (((fourmis[i].x) === baseF.x) && ((fourmis[i].y) === baseF.y)) {
				matrice[baseF.x][baseF.y] = phero;
                fourmis[i].transporte = false;
            }

        } else {
			newX = fourmis[i].x;
			newY = fourmis[i].y;
			var pheromin = phero+1;
			for(var c = -20; c<21; c=c+20){
				for(var d = -20; d<21; d=d+20){
					if((dansLaGrille(fourmis[i].x+c, fourmis[i].y+d))&&(matrice[fourmis[i].x+c][fourmis[i].y+d]>0)&&(matrice[fourmis[i].x+c][fourmis[i].y+d]<pheromin)){
						pheromin = matrice[fourmis[i].x+c][fourmis[i].y+d];
						newX = fourmis[i].x+c;
						newY = fourmis[i].y+d;
					}
				}
			}
		}
		if(pheromin===phero+1){
			newX = fourmis[i].x + tabXY[Math.floor(Math.random() * 3)];
            newY = fourmis[i].y + tabXY[Math.floor(Math.random() * 3)];

            while (!dansLaGrille(newX, newY)) {
                newX = fourmis[i].x + tabXY[Math.floor(Math.random() * 3)];
                newY = fourmis[i].y + tabXY[Math.floor(Math.random() * 3)];
            }
        }
        var four = fourmis[i];
        fourmis[i].bouger(four, newX, newY);

        for (var unTas in tas) {
            if ((tas[unTas].taille > 0)&&(newX === tas[unTas].x)&&(newY === tas[unTas].y)) {
                fourmis[i].transporte = true;
                diminuer(tas[unTas]);
            }
        }
    }
	ctx.strokeRect(0,0,can.width,can.height);
	dessinerTas();
	dessinerBase(baseF, baseF.x, baseF.y);
	setTimeout(function () {
		window.requestAnimationFrame(loadGrille);
	}, vitesse);
}


window.requestAnimationFrame(loadGrille);