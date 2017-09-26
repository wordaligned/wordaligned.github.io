var sqs = [{x:6,y:6},{x:8,y:7},{x:10,y:6},{x:8,y:5},{x:10,y:4},{x:9,y:2},{x:7,y:1},{x:8,y:3},{x:6,y:2},{x:4,y:1},{x:2,y:2},{x:1,y:4},{x:3,y:5},{x:4,y:3},{x:3,y:1},{x:5,y:2},{x:6,y:4},{x:4,y:5},{x:5,y:7},{x:3,y:8},{x:4,y:10},{x:6,y:9},{x:4,y:8},{x:2,y:9},{x:1,y:7},{x:3,y:6},{x:5,y:5},{x:7,y:4},{x:8,y:6},{x:10,y:5},{x:9,y:7},{x:10,y:9},{x:8,y:10},{x:7,y:8},{x:5,y:9},{x:6,y:7},{x:8,y:8},{x:7,y:10},{x:9,y:9},{x:10,y:7},{x:9,y:5},{x:7,y:6},{x:8,y:4},{x:10,y:3},{x:9,y:1},{x:7,y:2},{x:5,y:3},{x:6,y:1},{x:7,y:3},{x:9,y:4},{x:10,y:2},{x:8,y:1},{x:9,y:3},{x:10,y:1},{x:8,y:2},{x:6,y:3},{x:5,y:1},{x:3,y:2},{x:1,y:1},{x:2,y:3},{x:1,y:5},{x:2,y:7},{x:1,y:9},{x:3,y:10},{x:2,y:8},{x:3,y:9},{x:5,y:10},{x:6,y:8},{x:4,y:7},{x:2,y:6},{x:1,y:8},{x:2,y:10},{x:4,y:9},{x:6,y:10},{x:8,y:9},{x:10,y:10},{x:9,y:8},{x:7,y:7},{x:6,y:5},{x:4,y:6},{x:3,y:4},{x:4,y:2},{x:2,y:1},{x:1,y:3},{x:2,y:5},{x:4,y:4},{x:5,y:6},{x:3,y:7},{x:5,y:8},{x:7,y:9},{x:9,y:10},{x:10,y:8},{x:9,y:6},{x:7,y:5},{x:5,y:4},{x:3,y:3},{x:1,y:2},{x:2,y:4},{x:1,y:6}];

$(document).ready(function(){

    var knight = $('#knight');
    var counter = $('#counter');
    var i = 1;
    var delay_msecs = 1600;
    var k_pos = function(xy) {
        var x = xy.x - 1, y = xy.y - 1;
        return { left: (x * 660 / 9) + "px", top: (y * 680 / 9) + "px" }
    }
    var next = function() {
        ++i;
        counter.text("" + i);
    }
    var k_move = function() {
        if (i < 99) {
            knight.animate(k_pos(sqs[i]), delay_msecs, 0, function () { next(); k_move(); });
        } else {
            i = 1;
        }
    }
    var pause = function() {
        knight.stop(true).animate(k_pos(sqs[i]), delay_msecs, 0, next);
        $('#toggle').attr('title', 'Play').off('click').click(play).html('<img src="./images/play_icon.png" />');
    }
    var play = function() {
        $('#toggle').attr('title', 'Pause').off('click').click(pause).html('<img src="./images/pause_icon.png" />');
        k_move();
    }
    var reset = function() {
        pause();
        knight.stop(true).css({top: "378px", left: "367px"});
        counter.text("1");
        i = 1;
        delay_msecs = 1600.;
    }
    var step = function() {
        pause();
    }
    var clinamen = function() {
        i = 64;
        delay_msecs = 1600.;
        pause();
    }
    var keydown = function(e) {
        switch (e.which) {
        case 66: clinamen(); break;
        case 80: $('#toggle').click(); break;
        case 82: reset(); break;
        case 83: step(); break;
        }
    }
    $('#clinamen').click(clinamen);
    $('#faster').click(function () { delay_msecs *= 0.5; });
    $('#slower').click(function () { delay_msecs *= 2.0; });
    $('#toggle').click(play);
    $('#step').click(step);
    $('#clear').click(reset);
    $(this).keydown(keydown);
});
