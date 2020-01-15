#include <stdlib.h>
#include <math.h>
#include "VapourSynth.h"
#include "VSHelper.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CLAMP(a, b, c) (MIN(MAX(a, b), c))

int diagram_bounds[1000][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, { 74 ,  85 }, { 68 ,  92 }, { 65 ,  96 }, { 62 ,  100 }, { 60 ,  103 }, { 58 ,  106 }, { 56 ,  109 }, { 54 ,  112 }, { 53 ,  114 }, { 52 ,  117 }, { 50 ,  119 }, { 49 ,  121 }, { 47 ,  123 }, { 47 ,  126 }, { 45 ,  127 }, { 45 ,  130 }, { 43 ,  132 }, { 43 ,  134 }, { 41 ,  136 }, { 41 ,  137 }, { 40 ,  140 }, { 39 ,  141 }, { 38 ,  143 }, { 38 ,  145 }, { 37 ,  147 }, { 36 ,  149 }, { 36 ,  150 }, { 35 ,  152 }, { 34 ,  154 }, { 33 ,  156 }, { 33 ,  157 }, { 32 ,  159 }, { 32 ,  160 }, { 31 ,  162 }, { 31 ,  164 }, { 30 ,  166 }, { 29 ,  167 }, { 29 ,  169 }, { 29 ,  170 }, { 28 ,  172 }, { 28 ,  173 }, { 27 ,  175 }, { 27 ,  176 }, { 26 ,  178 }, { 26 ,  179 }, { 26 ,  181 }, { 25 ,  182 }, { 25 ,  184 }, { 24 ,  185 }, { 24 ,  187 }, { 23 ,  188 }, { 23 ,  190 }, { 23 ,  191 }, { 22 ,  193 }, { 22 ,  194 }, { 22 ,  196 }, { 21 ,  197 }, { 21 ,  199 }, { 20 ,  200 }, { 20 ,  202 }, { 20 ,  203 }, { 19 ,  204 }, { 19 ,  206 }, { 19 ,  207 }, { 19 ,  208 }, { 18 ,  210 }, { 18 ,  211 }, { 18 ,  212 }, { 17 ,  214 }, { 17 ,  215 }, { 17 ,  217 }, { 16 ,  218 }, { 16 ,  219 }, { 16 ,  220 }, { 16 ,  222 }, { 16 ,  223 }, { 15 ,  224 }, { 15 ,  225 }, { 15 ,  227 }, { 14 ,  228 }, { 14 ,  229 }, { 14 ,  230 }, { 14 ,  232 }, { 13 ,  233 }, { 13 ,  234 }, { 13 ,  235 }, { 13 ,  237 }, { 13 ,  238 }, { 12 ,  239 }, { 12 ,  240 }, { 12 ,  242 }, { 12 ,  243 }, { 12 ,  244 }, { 11 ,  246 }, { 11 ,  246 }, { 11 ,  248 }, { 11 ,  249 }, { 11 ,  250 }, { 10 ,  251 }, { 10 ,  253 }, { 10 ,  253 }, { 10 ,  255 }, { 10 ,  256 }, { 10 ,  257 }, { 10 ,  259 }, { 9 ,  259 }, { 9 ,  261 }, { 9 ,  262 }, { 9 ,  263 }, { 9 ,  264 }, { 9 ,  265 }, { 8 ,  266 }, { 8 ,  268 }, { 8 ,  269 }, { 8 ,  270 }, { 8 ,  271 }, { 8 ,  272 }, { 8 ,  274 }, { 7 ,  274 }, { 7 ,  276 }, { 7 ,  276 }, { 7 ,  278 }, { 7 ,  279 }, { 7 ,  280 }, { 7 ,  281 }, { 7 ,  282 }, { 7 ,  284 }, { 6 ,  284 }, { 6 ,  286 }, { 6 ,  287 }, { 6 ,  288 }, { 6 ,  289 }, { 6 ,  290 }, { 6 ,  292 }, { 6 ,  292 }, { 6 ,  294 }, { 6 ,  294 }, { 6 ,  296 }, { 6 ,  297 }, { 5 ,  298 }, { 5 ,  299 }, { 5 ,  300 }, { 5 ,  301 }, { 5 ,  302 }, { 5 ,  303 }, { 5 ,  304 }, { 5 ,  306 }, { 5 ,  307 }, { 5 ,  308 }, { 5 ,  309 }, { 5 ,  310 }, { 4 ,  311 }, { 4 ,  312 }, { 4 ,  313 }, { 4 ,  314 }, { 4 ,  315 }, { 4 ,  317 }, { 4 ,  317 }, { 4 ,  319 }, { 4 ,  319 }, { 4 ,  321 }, { 4 ,  322 }, { 4 ,  323 }, { 4 ,  324 }, { 4 ,  325 }, { 4 ,  326 }, { 4 ,  327 }, { 4 ,  328 }, { 4 ,  329 }, { 4 ,  330 }, { 4 ,  331 }, { 4 ,  332 }, { 4 ,  333 }, { 4 ,  334 }, { 3 ,  335 }, { 3 ,  337 }, { 3 ,  337 }, { 3 ,  339 }, { 3 ,  339 }, { 3 ,  341 }, { 3 ,  342 }, { 3 ,  343 }, { 3 ,  344 }, { 3 ,  345 }, { 3 ,  346 }, { 3 ,  347 }, { 3 ,  348 }, { 3 ,  349 }, { 3 ,  350 }, { 3 ,  351 }, { 3 ,  352 }, { 3 ,  353 }, { 3 ,  354 }, { 3 ,  355 }, { 3 ,  357 }, { 3 ,  357 }, { 3 ,  358 }, { 3 ,  359 }, { 3 ,  360 }, { 3 ,  362 }, { 3 ,  362 }, { 3 ,  364 }, { 3 ,  364 }, { 3 ,  366 }, { 3 ,  367 }, { 3 ,  367 }, { 3 ,  369 }, { 3 ,  369 }, { 3 ,  371 }, { 3 ,  372 }, { 3 ,  373 }, { 3 ,  374 }, { 3 ,  375 }, { 3 ,  376 }, { 3 ,  377 }, { 3 ,  378 }, { 3 ,  379 }, { 3 ,  380 }, { 3 ,  381 }, { 3 ,  382 }, { 3 ,  383 }, { 3 ,  384 }, { 3 ,  385 }, { 3 ,  386 }, { 3 ,  387 }, { 4 ,  388 }, { 4 ,  389 }, { 4 ,  390 }, { 4 ,  391 }, { 4 ,  392 }, { 4 ,  393 }, { 4 ,  394 }, { 4 ,  395 }, { 4 ,  396 }, { 4 ,  397 }, { 4 ,  399 }, { 4 ,  399 }, { 4 ,  400 }, { 4 ,  401 }, { 4 ,  402 }, { 4 ,  404 }, { 4 ,  404 }, { 4 ,  406 }, { 4 ,  406 }, { 4 ,  408 }, { 4 ,  409 }, { 4 ,  409 }, { 4 ,  411 }, { 4 ,  411 }, { 4 ,  413 }, { 5 ,  414 }, { 5 ,  415 }, { 5 ,  416 }, { 5 ,  416 }, { 5 ,  418 }, { 5 ,  418 }, { 5 ,  420 }, { 5 ,  421 }, { 5 ,  422 }, { 5 ,  423 }, { 5 ,  423 }, { 5 ,  425 }, { 5 ,  426 }, { 5 ,  427 }, { 5 ,  428 }, { 5 ,  429 }, { 5 ,  430 }, { 6 ,  430 }, { 6 ,  432 }, { 6 ,  433 }, { 6 ,  434 }, { 6 ,  435 }, { 6 ,  436 }, { 6 ,  437 }, { 6 ,  438 }, { 6 ,  439 }, { 6 ,  440 }, { 6 ,  441 }, { 6 ,  442 }, { 6 ,  443 }, { 6 ,  444 }, { 6 ,  445 }, { 7 ,  446 }, { 7 ,  447 }, { 7 ,  448 }, { 7 ,  449 }, { 7 ,  450 }, { 7 ,  451 }, { 7 ,  452 }, { 7 ,  453 }, { 7 ,  454 }, { 7 ,  455 }, { 7 ,  456 }, { 7 ,  457 }, { 8 ,  458 }, { 8 ,  459 }, { 8 ,  460 }, { 8 ,  461 }, { 8 ,  462 }, { 8 ,  463 }, { 8 ,  464 }, { 8 ,  465 }, { 8 ,  466 }, { 8 ,  467 }, { 9 ,  468 }, { 9 ,  469 }, { 9 ,  470 }, { 9 ,  471 }, { 9 ,  472 }, { 9 ,  473 }, { 9 ,  474 }, { 9 ,  475 }, { 9 ,  476 }, { 9 ,  477 }, { 9 ,  478 }, { 9 ,  479 }, { 9 ,  480 }, { 10 ,  481 }, { 10 ,  482 }, { 10 ,  483 }, { 10 ,  484 }, { 10 ,  485 }, { 10 ,  486 }, { 10 ,  487 }, { 10 ,  488 }, { 10 ,  489 }, { 10 ,  490 }, { 11 ,  491 }, { 11 ,  492 }, { 11 ,  493 }, { 11 ,  494 }, { 11 ,  495 }, { 11 ,  496 }, { 11 ,  497 }, { 12 ,  498 }, { 12 ,  499 }, { 12 ,  500 }, { 12 ,  502 }, { 12 ,  502 }, { 12 ,  504 }, { 12 ,  504 }, { 12 ,  506 }, { 12 ,  506 }, { 12 ,  507 }, { 13 ,  508 }, { 13 ,  509 }, { 13 ,  510 }, { 13 ,  511 }, { 13 ,  512 }, { 13 ,  513 }, { 13 ,  514 }, { 13 ,  515 }, { 14 ,  516 }, { 14 ,  517 }, { 14 ,  518 }, { 14 ,  519 }, { 14 ,  520 }, { 14 ,  521 }, { 14 ,  522 }, { 14 ,  523 }, { 14 ,  525 }, { 14 ,  525 }, { 15 ,  527 }, { 15 ,  527 }, { 15 ,  528 }, { 15 ,  529 }, { 15 ,  530 }, { 15 ,  531 }, { 15 ,  532 }, { 16 ,  534 }, { 16 ,  534 }, { 16 ,  536 }, { 16 ,  536 }, { 16 ,  537 }, { 16 ,  539 }, { 16 ,  539 }, { 16 ,  541 }, { 17 ,  541 }, { 17 ,  542 }, { 17 ,  543 }, { 17 ,  544 }, { 17 ,  546 }, { 17 ,  546 }, { 17 ,  547 }, { 17 ,  549 }, { 18 ,  549 }, { 18 ,  551 }, { 18 ,  551 }, { 18 ,  552 }, { 18 ,  554 }, { 18 ,  554 }, { 18 ,  556 }, { 19 ,  557 }, { 19 ,  557 }, { 19 ,  559 }, { 19 ,  560 }, { 19 ,  560 }, { 20 ,  562 }, { 20 ,  563 }, { 20 ,  563 }, { 20 ,  565 }, { 20 ,  566 }, { 20 ,  566 }, { 20 ,  568 }, { 20 ,  569 }, { 21 ,  569 }, { 21 ,  571 }, { 21 ,  572 }, { 21 ,  572 }, { 21 ,  573 }, { 21 ,  575 }, { 21 ,  576 }, { 22 ,  576 }, { 22 ,  578 }, { 22 ,  579 }, { 22 ,  580 }, { 22 ,  580 }, { 23 ,  582 }, { 23 ,  583 }, { 23 ,  584 }, { 23 ,  584 }, { 23 ,  586 }, { 23 ,  587 }, { 23 ,  588 }, { 23 ,  588 }, { 24 ,  589 }, { 24 ,  591 }, { 24 ,  592 }, { 24 ,  593 }, { 24 ,  594 }, { 25 ,  594 }, { 25 ,  595 }, { 25 ,  597 }, { 25 ,  598 }, { 25 ,  599 }, { 25 ,  600 }, { 25 ,  601 }, { 26 ,  602 }, { 26 ,  603 }, { 26 ,  604 }, { 26 ,  605 }, { 26 ,  606 }, { 27 ,  607 }, { 27 ,  608 }, { 27 ,  609 }, { 27 ,  610 }, { 27 ,  611 }, { 27 ,  612 }, { 27 ,  613 }, { 28 ,  614 }, { 28 ,  615 }, { 28 ,  616 }, { 28 ,  617 }, { 28 ,  618 }, { 29 ,  619 }, { 29 ,  620 }, { 29 ,  621 }, { 29 ,  622 }, { 29 ,  623 }, { 29 ,  624 }, { 29 ,  625 }, { 29 ,  626 }, { 30 ,  627 }, { 30 ,  628 }, { 30 ,  629 }, { 30 ,  630 }, { 31 ,  631 }, { 31 ,  632 }, { 31 ,  633 }, { 31 ,  634 }, { 31 ,  635 }, { 32 ,  636 }, { 32 ,  637 }, { 32 ,  638 }, { 32 ,  639 }, { 32 ,  640 }, { 33 ,  641 }, { 33 ,  642 }, { 33 ,  643 }, { 33 ,  644 }, { 33 ,  645 }, { 33 ,  646 }, { 33 ,  647 }, { 34 ,  648 }, { 34 ,  649 }, { 34 ,  650 }, { 34 ,  651 }, { 34 ,  652 }, { 35 ,  653 }, { 35 ,  654 }, { 35 ,  655 }, { 35 ,  656 }, { 35 ,  657 }, { 36 ,  658 }, { 36 ,  659 }, { 36 ,  660 }, { 36 ,  661 }, { 37 ,  662 }, { 37 ,  663 }, { 37 ,  664 }, { 37 ,  665 }, { 37 ,  666 }, { 37 ,  667 }, { 37 ,  668 }, { 38 ,  669 }, { 38 ,  670 }, { 38 ,  671 }, { 38 ,  672 }, { 38 ,  673 }, { 39 ,  674 }, { 39 ,  675 }, { 39 ,  676 }, { 39 ,  677 }, { 40 ,  678 }, { 40 ,  679 }, { 40 ,  680 }, { 40 ,  681 }, { 40 ,  682 }, { 41 ,  683 }, { 41 ,  684 }, { 41 ,  685 }, { 41 ,  686 }, { 42 ,  687 }, { 42 ,  688 }, { 42 ,  689 }, { 42 ,  690 }, { 42 ,  691 }, { 43 ,  692 }, { 43 ,  693 }, { 43 ,  694 }, { 43 ,  695 }, { 43 ,  696 }, { 43 ,  697 }, { 44 ,  698 }, { 44 ,  699 }, { 44 ,  700 }, { 44 ,  701 }, { 44 ,  702 }, { 45 ,  703 }, { 45 ,  704 }, { 45 ,  705 }, { 45 ,  706 }, { 46 ,  707 }, { 46 ,  708 }, { 46 ,  709 }, { 46 ,  710 }, { 47 ,  711 }, { 47 ,  712 }, { 47 ,  713 }, { 47 ,  714 }, { 48 ,  715 }, { 48 ,  716 }, { 48 ,  717 }, { 48 ,  718 }, { 48 ,  719 }, { 49 ,  720 }, { 49 ,  721 }, { 49 ,  722 }, { 49 ,  723 }, { 49 ,  724 }, { 49 ,  725 }, { 50 ,  726 }, { 50 ,  727 }, { 50 ,  728 }, { 50 ,  729 }, { 51 ,  730 }, { 51 ,  731 }, { 51 ,  732 }, { 51 ,  733 }, { 52 ,  730 }, { 52 ,  728 }, { 52 ,  726 }, { 52 ,  724 }, { 53 ,  722 }, { 53 ,  720 }, { 53 ,  717 }, { 53 ,  715 }, { 54 ,  713 }, { 54 ,  711 }, { 54 ,  709 }, { 54 ,  707 }, { 55 ,  705 }, { 55 ,  702 }, { 55 ,  700 }, { 55 ,  698 }, { 56 ,  696 }, { 56 ,  694 }, { 56 ,  692 }, { 56 ,  690 }, { 56 ,  687 }, { 57 ,  685 }, { 57 ,  683 }, { 57 ,  681 }, { 57 ,  679 }, { 58 ,  677 }, { 58 ,  675 }, { 58 ,  672 }, { 58 ,  670 }, { 59 ,  668 }, { 59 ,  666 }, { 59 ,  664 }, { 60 ,  662 }, { 60 ,  660 }, { 60 ,  657 }, { 60 ,  655 }, { 61 ,  653 }, { 61 ,  651 }, { 61 ,  649 }, { 62 ,  647 }, { 62 ,  645 }, { 62 ,  642 }, { 62 ,  640 }, { 62 ,  638 }, { 62 ,  636 }, { 63 ,  634 }, { 63 ,  632 }, { 63 ,  629 }, { 64 ,  627 }, { 64 ,  625 }, { 64 ,  623 }, { 64 ,  621 }, { 65 ,  619 }, { 65 ,  617 }, { 65 ,  614 }, { 66 ,  612 }, { 66 ,  610 }, { 66 ,  608 }, { 67 ,  606 }, { 67 ,  604 }, { 67 ,  602 }, { 67 ,  599 }, { 68 ,  597 }, { 68 ,  595 }, { 68 ,  593 }, { 69 ,  591 }, { 69 ,  589 }, { 69 ,  587 }, { 70 ,  584 }, { 70 ,  582 }, { 70 ,  580 }, { 71 ,  578 }, { 71 ,  576 }, { 71 ,  574 }, { 71 ,  572 }, { 71 ,  569 }, { 72 ,  567 }, { 72 ,  565 }, { 72 ,  563 }, { 73 ,  561 }, { 73 ,  559 }, { 73 ,  557 }, { 74 ,  554 }, { 74 ,  552 }, { 74 ,  550 }, { 75 ,  548 }, { 75 ,  546 }, { 75 ,  544 }, { 76 ,  541 }, { 76 ,  539 }, { 76 ,  537 }, { 77 ,  535 }, { 77 ,  533 }, { 77 ,  531 }, { 78 ,  529 }, { 78 ,  526 }, { 78 ,  524 }, { 78 ,  522 }, { 79 ,  520 }, { 79 ,  518 }, { 79 ,  516 }, { 80 ,  514 }, { 80 ,  511 }, { 81 ,  509 }, { 81 ,  507 }, { 81 ,  505 }, { 82 ,  503 }, { 82 ,  501 }, { 82 ,  499 }, { 83 ,  496 }, { 83 ,  494 }, { 83 ,  492 }, { 83 ,  490 }, { 84 ,  488 }, { 84 ,  486 }, { 85 ,  484 }, { 85 ,  481 }, { 85 ,  479 }, { 86 ,  477 }, { 86 ,  475 }, { 86 ,  473 }, { 87 ,  471 }, { 87 ,  469 }, { 87 ,  466 }, { 88 ,  464 }, { 88 ,  462 }, { 89 ,  460 }, { 89 ,  458 }, { 89 ,  456 }, { 89 ,  454 }, { 90 ,  451 }, { 90 ,  449 }, { 91 ,  447 }, { 91 ,  445 }, { 92 ,  443 }, { 92 ,  441 }, { 92 ,  438 }, { 93 ,  436 }, { 93 ,  434 }, { 94 ,  432 }, { 94 ,  430 }, { 94 ,  428 }, { 94 ,  426 }, { 95 ,  423 }, { 95 ,  421 }, { 95 ,  419 }, { 96 ,  417 }, { 96 ,  415 }, { 97 ,  413 }, { 97 ,  411 }, { 97 ,  408 }, { 98 ,  406 }, { 98 ,  404 }, { 99 ,  402 }, { 99 ,  400 }, { 100 ,  398 }, { 100 ,  396 }, { 100 ,  393 }, { 101 ,  391 }, { 101 ,  389 }, { 101 ,  387 }, { 102 ,  385 }, { 102 ,  383 }, { 103 ,  381 }, { 103 ,  378 }, { 104 ,  376 }, { 104 ,  374 }, { 104 ,  372 }, { 105 ,  370 }, { 105 ,  368 }, { 106 ,  366 }, { 106 ,  363 }, { 106 ,  361 }, { 107 ,  359 }, { 107 ,  357 }, { 108 ,  355 }, { 108 ,  353 }, { 109 ,  350 }, { 109 ,  348 }, { 110 ,  346 }, { 110 ,  344 }, { 110 ,  342 }, { 111 ,  340 }, { 111 ,  338 }, { 112 ,  335 }, { 112 ,  333 }, { 113 ,  331 }, { 113 ,  329 }, { 114 ,  327 }, { 114 ,  325 }, { 115 ,  323 }, { 115 ,  320 }, { 115 ,  318 }, { 116 ,  316 }, { 117 ,  314 }, { 117 ,  312 }, { 118 ,  310 }, { 118 ,  308 }, { 119 ,  305 }, { 119 ,  303 }, { 120 ,  301 }, { 120 ,  299 }, { 121 ,  297 }, { 121 ,  295 }, { 122 ,  293 }, { 122 ,  290 }, { 123 ,  288 }, { 123 ,  286 }, { 124 ,  284 }, { 125 ,  282 }, { 125 ,  280 }, { 126 ,  278 }, { 126 ,  275 }, { 127 ,  273 }, { 128 ,  271 }, { 128 ,  269 }, { 129 ,  267 }, { 129 ,  265 }, { 130 ,  262 }, { 131 ,  260 }, { 131 ,  258 }, { 132 ,  256 }, { 133 ,  254 }, { 133 ,  252 }, { 134 ,  250 }, { 135 ,  247 }, { 136 ,  245 }, { 136 ,  243 }, { 137 ,  241 }, { 138 ,  239 }, { 139 ,  237 }, { 139 ,  235 }, { 140 ,  232 }, { 141 ,  230 }, { 142 ,  228 }, { 143 ,  226 }, { 144 ,  224 }, { 145 ,  222 }, { 146 ,  220 }, { 147 ,  217 }, { 148 ,  215 }, { 149 ,  213 }, { 150 ,  211 }, { 151 ,  209 }, { 152 ,  207 }, { 153 ,  205 }, { 155 ,  202 }, { 156 ,  200 }, { 157 ,  198 }, { 158 ,  196 }, { 159 ,  194 }, { 160 ,  192 }, { 161 ,  190 }, { 162 ,  187 }, { 164 ,  185 }, { 165 ,  183 }, { 166 ,  181 }, { 167 ,  179 }, { 168 ,  177 }, { 169 ,  175 }, { 171 ,  174 }, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};

double sRGB_MATRIX[3][3] = {{ 3.2404542, -1.5371385, -0.4985314},
                     {-0.9692660,  1.8760108, 0.0415560 },
                     { 0.0556434, -0.2040259, 1.0572252 }};
// BGR primaries
double DCI_P3_PRIMARIES[3][2] = {{ 0.150, 0.060 } , { 0.265, 0.690 }, { 0.680, 0.320 }};
double SRGB_PRIMARIES[3][2] = {{0.15, 0.06}, {0.3, 0.6}, {0.64, 0.33}};
double ADOBE98_PRIMARIES[3][2] = {{0.15, 0.06}, {0.21, 0.71}, {0.64, 0.33}};
double ADOBEWIDE_PRIMARIES[3][2] = {{0.15664, 0.01770}, {0.11416, 0.82621}, {0.73469, 0.26539}};
double APPLE_PRIMARIES[3][2] = {{0.155, 0.018}, {0.280, 0.826}, {0.625, 0.265}};
double CIERGB_PRIMARIES[3][2] = {{ 0.1666 , 0.0089  }, { 0.2738 , 0.7174  }, { 0.7347 , 0.2653  }};
double REC_470_M_PRIMARIES[3][2] = { { 0.670, 0.330 }, { 0.210, 0.710 }, { 0.140, 0.080 } };
double REC_470_BG_PRIMARIES[3][2] = { { 0.640, 0.330 }, { 0.290, 0.600 }, { 0.150, 0.060 } };
double SMPTE_C_PRIMARIES[3][2] = { { 0.630, 0.340 }, { 0.310, 0.595 }, { 0.155, 0.070 } };
double FILMC_PRIMARIES[3][2] = { { 0.681, 0.319 }, { 0.243, 0.692 }, { 0.145, 0.049 } };
double REC_2020_PRIMARIES[3][2] = { { 0.708, 0.292 }, { 0.170, 0.797 }, { 0.131, 0.046 } };
double JEDEC_P22_PRIMARIES[3][2] = { { 0.630, 0.340 }, { 0.295, 0.605 }, { 0.155, 0.077 } };

double E_TO_D65[3][3] = {{0.9531874, -0.0265906,  0.0238731},
                         {-0.0382467,  1.0288406,  0.0094060},
                         {0.0026068, -0.0030332, 1.0892565}};

typedef struct {
    VSNodeRef *node;
    char* reference_gamut;
    double darken;
    const VSVideoInfo *vi;
} FilterData;

static void VS_CC showInit(VSMap *in, VSMap *out, void **instanceData, VSNode *node, VSCore *core, const VSAPI *vsapi) {
    FilterData *d = (FilterData *) * instanceData;
    VSVideoInfo new_vi = (VSVideoInfo) * (d->vi);
    new_vi.width = 1000;
    new_vi.height = 1000;
    new_vi.format = vsapi->getFormatPreset(pfRGBS, core);
    vsapi->setVideoInfo(&new_vi, 1, node);
}

void mat_mul_vec(double M[3][3], double * vector) {
    double out[3] = {0., 0., 0.};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            out[i] += M[i][j] * vector[j];
    }
    memcpy(vector, out, 3*sizeof(double));
}

void xyy_to_XYZ (double * xyy) {
    double XYZ[3] = { (double) xyy[0]*xyy[2]/xyy[1],
                      (double) xyy[2],
                      (double) (1 - xyy[0] - xyy[1]) * xyy[2] / xyy[1] };

    memcpy(xyy, XYZ, 3*sizeof(double));
}

void draw_diagram(float * dstp[3], int dst_stride) {
    for (int y = 0; y < 1000; ++y) {
        for (int x = 0; x < 1000; ++x) {
            double xyy[3] = {x/999., (999-y)/999., 1.};
            xyy_to_XYZ(xyy);

            mat_mul_vec(sRGB_MATRIX, xyy);
            int within_bounds = x >= diagram_bounds[y][0] && x <= diagram_bounds[y][1]+1;

            // desaturate (don’t really get why this works so well tbh, but it looks like shit if you don’t do this)
            double max = MAX(xyy[2], MAX(xyy[0], xyy[1]));
            if (max > 1)
                for (int i = 0; i < 3; ++i)
                    xyy[i] *= 1/max;

            for (int i = 0; i < 3; ++i)
                dstp[i][x + y * dst_stride] = within_bounds ? CLAMP(pow(xyy[i], 1/2.2), 0., 1.) : 1.f;
        }
    }
}

int PointInTriangle (double px, double py, double p0x, double p0y, double p1x, double p1y, double p2x, double p2y) {
    double Area = 0.5 *(-p1y*p2x + p0y*(-p1x + p2x) + p0x*(p1y - p2y) + p1x*p2y);
    double s = 1/(2*Area)*(p0y*p2x - p0x*p2y + (p2y - p0y)*px + (p0x - p2x)*py);
    double t = 1/(2*Area)*(p0x*p1y - p0y*p1x + (p0y - p1y)*px + (p1x - p0x)*py);
    return s >= 0 && t >= 0 && (1-s-t) >= 0;
}

void draw_standard_gamut(float * dstp[3], int dst_stride, char* standard) {
    double prims[3][2];

    #define GAMUT_OPT(string, primaries) else if (strcmp(standard, string) == 0) memcpy(prims, primaries, sizeof(prims));
    if (strcmp(standard, "709") == 0 || strcmp(standard, "srgb") == 0)
            memcpy(prims, SRGB_PRIMARIES, sizeof(prims));
    GAMUT_OPT("dcip3", DCI_P3_PRIMARIES)
    GAMUT_OPT("adobe98", ADOBE98_PRIMARIES)
    GAMUT_OPT("adobewide", ADOBEWIDE_PRIMARIES)
    GAMUT_OPT("apple", APPLE_PRIMARIES)
    GAMUT_OPT("ciergb", CIERGB_PRIMARIES)
    GAMUT_OPT("filmc", FILMC_PRIMARIES)
    GAMUT_OPT("jedec_p22", JEDEC_P22_PRIMARIES)
    GAMUT_OPT("470bg", REC_470_BG_PRIMARIES)
    GAMUT_OPT("470m", REC_470_M_PRIMARIES)
    GAMUT_OPT("2020", REC_2020_PRIMARIES)
    GAMUT_OPT("smpte_c", SMPTE_C_PRIMARIES)
    else
        return;

    for (int y = 0; y < 1000; y++) for (int x = 0; x < 1000; x++)
        if (!PointInTriangle(x/999., y/999., prims[0][0], prims[0][1], prims[1][0], prims[1][1], prims[2][0], prims[2][1]))
            for (int i = 0; i < 3; ++i) {
                dstp[i][x + (999-y) * dst_stride] += 0.15f;
                dstp[i][x + (999-y) * dst_stride] *= 0.3f;
            }
}

void draw_gamut(float * dstp[3], int dst_stride, float * srcp[3], int src_stride, int ih, int iw, double darken) {
    for (int y = 0; y < ih; y++)
        for (int x = 0; x < iw; x++) {
            double XYZ[3] = {(double) srcp[0][x + y * src_stride],
                             (double) srcp[1][x + y * src_stride],
                             (double) srcp[2][x + y * src_stride]};

            mat_mul_vec(E_TO_D65, XYZ); // based Bruce Lindbloom

            double xy[2] = {XYZ[0] / (XYZ[0] + XYZ[1] + XYZ[2]),
                            XYZ[1] / (XYZ[0] + XYZ[1] + XYZ[2])};
            int chrx = CLAMP((int) round(xy[0] * 999), 0, 999);
            int chry = 999 - CLAMP((int) round(xy[1] * 999), 0, 999);

            for (int i = 0; i < 3; ++i)
                dstp[i][chrx + chry * dst_stride] *= (float) darken;
        }
}

static const VSFrameRef *VS_CC showGetFrame(int n, int activationReason, void **instanceData, void **frameData, VSFrameContext *frameCtx, VSCore *core, const VSAPI *vsapi) {
    FilterData *d = (FilterData *) * instanceData;

    if (activationReason == arInitial) {
        vsapi->requestFrameFilter(n, d->node, frameCtx);
    } else if (activationReason == arAllFramesReady) {
        const VSFrameRef *frame = vsapi->getFrameFilter(n, d->node, frameCtx);

        VSFrameRef *dst = vsapi->newVideoFrame(vsapi->getFormatPreset(pfRGBS, core), 1000, 1000, frame, core);

        int ih = vsapi->getFrameHeight(frame, 0);
        int iw = vsapi->getFrameWidth(frame, 0);

        float *srcp[3], *dstp[3];
        for (int i = 0; i < 3; ++i) {
            srcp[i] = (float *) vsapi->getWritePtr(frame, i);
            dstp[i] = (float *) vsapi->getWritePtr(dst, i);
        }
        int src_stride = vsapi->getStride(frame, 0) / sizeof(float), dst_stride = vsapi->getStride(dst, 0) / sizeof(float);

        draw_diagram(dstp, dst_stride);
        draw_gamut(dstp, dst_stride, srcp, src_stride, ih, iw, d->darken);
        if (d->reference_gamut != NULL)
            draw_standard_gamut(dstp, dst_stride, d->reference_gamut);

        vsapi->freeFrame(frame);
        return dst;
    }

    return 0;
}

static void VS_CC showFree(void *instanceData, VSCore *core, const VSAPI *vsapi) {
    FilterData *d = (FilterData *)instanceData;
    vsapi->freeNode(d->node);
    free(d->reference_gamut);
    free(d);
}

static void VS_CC showCreate(const VSMap *in, VSMap *out, void *userData, VSCore *core, const VSAPI *vsapi) {
    FilterData d;
    FilterData *data;
    int err;

    d.node = vsapi->propGetNode(in, "clip", 0, 0);
    d.vi = vsapi->getVideoInfo(d.node);

    d.reference_gamut = malloc(sizeof(char)*30);
    char* gamut = vsapi->propGetData(in, "gamut", 0, &err);
    if (err)
        d.reference_gamut = NULL;
    else
        strcpy(d.reference_gamut, gamut);

    d.darken = vsapi->propGetFloat(in, "darken", 0, &err);
    if (err)
        d.darken = 0.6;

    data = malloc(sizeof(d));
    *data = d;

    vsapi->createFilter(in, out, "ShowGamut", showInit, showGetFrame, showFree, fmParallel, 0, data, core);
}

//////////////////////////////////////////
// Init

VS_EXTERNAL_API(void) VapourSynthPluginInit(VSConfigPlugin configFunc, VSRegisterFunction registerFunc, VSPlugin *plugin) {
    configFunc("com.lypheo.colortools", "color", "VapourSynth Color Tools", VAPOURSYNTH_API_VERSION, 1, plugin);
    registerFunc("ShowGamut", "clip:clip;gamut:data:opt;darken:float:opt", showCreate, 0, plugin);
}