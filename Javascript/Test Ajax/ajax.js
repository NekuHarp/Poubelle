window.addEventListener("load", load);

function chapitre(i) {
	document.getElementById("link0").textContent = "";
	document.getElementById("link1").textContent = "";
	document.getElementById("link2").textContent = "";
	document.getElementById("link0").setAttribute("href","");
	document.getElementById("link1").setAttribute("href","");
	document.getElementById("link2").setAttribute("href","");
	var req = new XMLHttpRequest();
	var url = "chapitre" + i + ".json";
	req.open("GET", url);
	req.onerror = function() {
    console.log("Échec de chargement "+url);
	};
	req.onload = function() {
		if (req.status === 200) {
			var data = JSON.parse(req.responseText);
			document.getElementById("text").textContent = data.txt;
			for(j=0;j<3;j++){
				if(data.links[j]){
					document.getElementById("link"+j).textContent = data.links[j].txt;
					document.getElementById("link"+j).setAttribute("href",data.links[j].link);
				}
			}
		} else {
		  console.log("Erreur " + req.status);
		}
	};
	req.send();
}

function load() {
	var link = window.location.href;
	var x = link.split("#");
	if(x[1]!=null) {
		chapitre(x[1]);
	} else {
		chapitre(1);
	}
}