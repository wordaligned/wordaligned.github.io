$(function() {
    var xs = $("#xs"), sort = $("#sort"), mode = 0;

    var animate = function() {
        var m = mode++ % 4;
        if (m == 0) {
            xs.text("list(range(10))");
            sort.text("clear()");
        } else if (m == 1) {
            xs.text("list(range(10))");
            sort.text("sort()");
        } else if (m == 2) {
            xs.text("[6, 6, 6]");
            sort.text("sort()");
        } else if (m == 3) {
            xs.text("list(range(10))");
            sort.text("sort()");
        }
    }

    $(this).keydown(function(e) {
        if (e.which == 84) {
            animate();
        }
    });

});
