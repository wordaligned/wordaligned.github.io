$(function() {
    var mode = 0, kmode = 0;
    var sicp = $(".sicp"), sicp1 = $(".sicp1"), sicp2 = $(".sicp2");
    var kword = $("#keywords");
    var cc = sicp.css("color");
    var poem = $('#concretepoem');
    var n_lines = $("#concretepoem > li").length;

    var rotate_poem = function (n) {
        if (n > 0) {
            poem.append($("#concretepoem > li").first().detach());
            setTimeout(rotate_poem, 1000, n - 1);
        }
    }

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

    $('.palindrome').textillate({
        autoStart: false,
        out: { effect: 'fadeInLeftBig',   shuffle: false, reverse: true, delay: 1000 },
        in:  { effect: 'fadeOutRightBig', shuffle: false, reverse: true, delay: 1000 }
    });
    $('.emordnilap').textillate({
        autoStart: false,
        in:  { effect: 'fadeInRightBig', shuffle: false, delay: 1000 },
        out: { effect: 'fadeOutLeftBig', shuffle: false, delay: 1000 }
    });

    $(this).keydown(function(e) {
        if (e.which == 66) {
            emphasis();
        }
        if (e.which == 75) {
            next_keyword();
        }
        if (e.which == 82) {
            rotate_poem(n_lines);
        }
        if (e.which == 84) {
            $('.emordnilap').textillate('in');
            $('.palindrome').textillate('in');
            $('.palindrome').on('inAnimationEnd.tlt', function () {
                $(this).show();
            });
        }
    });
});
