$(function() {
    var mode = 0;
    var hi = $(".hi"), hi1 = $(".hi1"), hi2 = $(".hi2");
    var cc = hi.css("color");

    var emphasis = function () {
        var m = mode++ % 3;
        if (m == 0) {
            hi.css({color:"#666"});
            hi1.css({color:cc});
            hi2.css({color:"#666"});
        } else if (m == 1) {
            hi1.css({color:cc});
            hi2.css({color:cc});
        } else if (m == 2) {
            hi1.css({color:cc});
            hi2.css({color:cc});
            hi.css({color:cc});
        }
    }

    $(this).keydown(function(e) {
        if (e.which == 67) {
            emphasis();
        }
    });

});
