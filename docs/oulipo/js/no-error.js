$(function() {            
    var poem = $('#concretepoem');

    var rotate_poem = function () {        
        poem.append($("#concretepoem > li").first().detach());
        setTimeout(rotate_poem, 1000);
    }

    $(this).keydown(function(e) {
        if (e.which == 82) {
            rotate_poem();
        }
    });
});
