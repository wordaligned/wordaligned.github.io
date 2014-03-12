// Return an integer chosen at random from the half open range [lo, hi)
function randrange(lo, hi) {
    return lo + Math.floor((hi - lo) * Math.random());
}

// Return the last element in an Array
// The caller must ensure the array is not empty
function last(xs) {
    return xs[xs.length - 1];
}

// Shuffle an array, xs, in place.
function randomshuffle(xs) {
    var i = xs.length;
    var r, tmp;
    while (i-- != 0) {
        r = randrange(0, i + 1);
        tmp = xs[i];
        xs[i] = xs[r];
        xs[r] = tmp;
    }
    return xs;
}

// Places a card on a pile, using optimal patience sort strategy.
function place_on_pile(card, piles) {
    var p = 0;
    // A binary search through pile-tops should be more efficient.
    // For a deck of just 52 cards, this doesn't really matter.
    while (p != piles.length && card >= last(piles[p])) {
        ++p;
    }
    if (p == piles.length) {
        piles.push([]);
    }
    piles[p].push(card);
    return p;
}

// Patience sort.
// Returns any array of moves [{card, pile, pile-depth}*]
function patience_sort(cards) {
    var piles = [];
    var moves = [];
    for (var i = 0; i != cards.length; ++i) {
        var pile = place_on_pile(cards[i], piles);
        moves.push({card: cards[i], pile: pile, depth: piles[pile].length});
    }
    return moves;
}
