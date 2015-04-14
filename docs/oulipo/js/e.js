$(function() {   
    var mode = 0, kmode = 0;
    var sicp = $(".sicp"), sicp1 = $(".sicp1"), sicp2 = $(".sicp2");
    var kword = $("#keywords");
    var cc = sicp.css("color");

    var emphasis = function () {
        var m = mode++ % 3;
        if (m == 0) {
            sicp.css({color:"#bbb"});
            sicp1.css({color:"#930"});
            sicp2.css({color:"#bbb"});
        } else if (m == 1) {
            sicp1.css({color:"#bbb"});
            sicp2.css({color:"#930"});
        } else if (m == 2) {
            sicp.css({color:cc});
            sicp1.css({color:cc});
            sicp2.css({color:cc});
        }
    }

    var next_keyword = function () {
        kws = [ "if", "do", "try", "while", "friend", "true", "union", "private", "false", "break", "final" ];
        kword.text(kws[++kmode % kws.length]);
    }

    $(this).keydown(function(e) {
        if (e.which == 66) {
            emphasis();
        }
        if (e.which == 75) {
            next_keyword();
        }
    });
});
