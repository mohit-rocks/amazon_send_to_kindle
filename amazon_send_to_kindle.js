(function($){
	Drupal.behaviors.amazon_send_to_kindle = {
		attach: function (context, settings) {
			$(function(k){
        window.$SendToKindle&&window.$SendToKindle.Widget?$SendToKindle.Widget.init({"title":".title","published":".submitted","content":".content","exclude":".field-name-field-specialities"}):setTimeout(k,500);
			})();
		}
	};
})(jQuery);
