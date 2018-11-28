window.addEventListener("load", main);

function main() {
	date = new Date();
	i=0;
	document.getElementById("addAlarm").addEventListener("click",addAlarm);
	refreshTime();
}

function refreshTime() {
	date.setTime(Date.now());
	
	h = date.getHours();
	m = date.getMinutes();
	s = date.getSeconds();
	
	document.getElementById("heures").textContent = h;
	document.getElementById("minutes").textContent = m;
	document.getElementById("secondes").textContent = s;
	
	setTimeout(refreshTime, 1000);
	setTimeout(checkAlarm, 1000);
}

function checkAlarm() {
	j=1;
	while(i>=j){
		if(document.getElementById(j)!=null){
			if(document.getElementById(j).checked) {
				if((h == document.getElementById("h"+j).value)&&(m == document.getElementById("m"+j).value)) {
				var audio = new Audio('alarme.mp3');
				audio.play();
				alert(document.getElementById("text"+j).value);
				}
			}
		}
		j=j+1;
	}
}

function remove(X) {
	var p = X.parentNode;
	var root = p.parentNode;
	root.removeChild(p);
}

function addAlarm() {
	i=i+1;
	div = document.createElement('div');
		div.setAttribute("id","alarm"+i)
	checkbox = document.createElement('input');
		checkbox.setAttribute("type","checkbox")
		checkbox.setAttribute("id",i)
	inputHeure = document.createElement('input');
		inputHeure.setAttribute("type","number")
		inputHeure.setAttribute("min","00")
		inputHeure.setAttribute("max","23")
		inputHeure.setAttribute("id","h"+i)
	inputMinute = document.createElement('input');
		inputMinute.setAttribute("type","number")
		inputMinute.setAttribute("min","00")
		inputMinute.setAttribute("max","59")
		inputMinute.setAttribute("id","m"+i)
	titre = document.createElement('input');
		titre.setAttribute("type","text")
	button = document.createElement('input');
		button.setAttribute("type","button")
		button.setAttribute("value","Delete")
		button.addEventListener("click",function(evt) { remove(this);});
	document.getElementById("alarm").appendChild(div);
	div.appendChild(checkbox);
	div.appendChild(inputHeure);
	div.appendChild(inputMinute);
	div.appendChild(titre);
	div.appendChild(button);
}