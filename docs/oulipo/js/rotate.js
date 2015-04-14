$(function() {            
    var poem = $('#concretepoem');

    var rotate_poem = function (n) {
        if (n > 0) {
            poem.append($("#concretepoem > li").first().detach());
            setTimeout(rotate_poem, 1000, n - 1);
        }
    }

    $(this).keydown(function(e) {
        if (e.which == 82) {
            rotate_poem(22);
            $(".concretee").css({color:"#930"});
        }
    });
});
