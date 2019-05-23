(function ($) {
    Drupal.behaviors.s1Load = {
        attach: function (context, settings) {
            function s1GetView() {
                var topHeight = $(window).scrollTop() + $(window).height();
                $('.s1[data-s1]:not(.ajax-progress):visible', context).each(function () {
                    var s1 = $(this);
                    if (s1.offset().top <= topHeight) {
                        s1.addClass('ajax-progress').load('/s1/load/' + s1.attr('data-s1'), function () {
                            $('> *:first', s1).addClass('s1-lod');
                            s1.replaceWith(s1.html());
                            $(window).trigger('resize');
                        });
                    }
                });
            }

            $(window).load(function () {
                s1GetView();
                $(document).scroll(function () {
                    s1GetView();
                });
            });
            $(window).resize(function () {
                if ($('.s1:not(.ajax-progress)', document).length) {
                    s1GetView();
                }
            });
            $(document).bind('documentChange', function () {
                if ($('.s1:not(.ajax-progress)', document).length) {
                    s1GetView();
                }
            });
            s1GetView();
        }
    };
})(jQuery);