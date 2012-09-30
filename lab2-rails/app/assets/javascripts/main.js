$(document).on("ready", function(){
 while(1){
	$.get(document.url, function(data){
		new_data = $(data).find("table");
		if (new_data
	});

 }

});


function getBody(element) {
	var divider = 2;
	var originalTable = element.clone();
	return 
	$(originalTable).children('tbody').children('tr').children('td').length;
}

