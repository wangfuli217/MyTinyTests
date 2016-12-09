

//申请空间, 线路的搜索结果写入文件
function write_to_file(city, type, out_str)
{
    var now_str = (new Date()).Format("yyyyMMdd_HHmmss")
    var new_file = city + "_" + type + "_" + now_str + ".txt";

    //申请空间, save to File
    window.webkitRequestFileSystem(window.TEMPORARY, 100*1024*1024, function onInitFs(fs) {
      //console.log('Opened file system: ' + fs.name);

      fs.root.getFile(new_file, {create: true}, function(fileEntry) {
            fileEntry.createWriter(function(writer) {
                writer.onerror = errorHandler;
                writer.onwriteend = function(e) {
                    console.log('write complete, file:' + new_file);
                };
                writer.write(new Blob([out_str], {type: 'text/plain'}));
            });
      }, errorHandler);
    }, errorHandler);
}

function write_city_lines_to_file(city, type, city_lines){

    //format
    var out_str = "count = " + city_lines.length + "\nvar city_lines = [";
    for (var i in city_lines){
        out_str += "\'" + city_lines[i] + "\'";
        if (i < city_lines.length - 1){
            out_str += ", ";
        }
    }
    out_str += "]";

    //把结果写入文件
    write_to_file(city, type, out_str);
}