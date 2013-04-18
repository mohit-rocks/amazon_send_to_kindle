(function($){
	Drupal.behaviors.amazon_send_to_kindle = {
		attach: function (context, settings) {
			$(function(k){
				window.$SendToKindle&&window.$SendToKindle.Widget?$SendToKindle.Widget.init({}):setTimeout(k,500);
			});
		}
	};
})(jQuery);