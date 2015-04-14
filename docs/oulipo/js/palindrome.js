$(function() {
    $('.palindrome').textillate({
        autoStart: false,
        out: {
           effect: 'fadeInLeftBig',
           shuffle: false,
            reverse: true,
           delay: 1000
       },
       in: {
           effect: 'fadeOutRightBig',
           shuffle: false,
           reverse: true,
           delay: 1000
       }
    });
    $('.emordnilap').textillate({
        autoStart: false,
        in: {
           effect: 'fadeInRightBig',
           shuffle: false,
           delay: 1000
       },
       out: {
           effect: 'fadeOutLeftBig',
           shuffle: false,
           delay: 1000
       },
    });

    $(this).keydown(function(e) {
        if (e.which == 84) {
            $('.emordnilap').textillate('in');
            $('.palindrome').textillate('in');
            $('.palindrome').on('inAnimationEnd.tlt', function () {
                $(this).show();
            });
        }
    });
});
