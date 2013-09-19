(function($) {
    $.fn.applyTagIts = function(placeholder, type) {
        var tagArea = this;
        switch(type) {
            case 'scenario':
                var id = $('li.name', tagArea).eq(0).data('scenario-tag-box');
                $('#scenario-input-'+id+'').tagit(
                    {
                        singleField: true,
                        singleFieldNode: $('#scenario-values-'+id+''),
                        placeholderText: placeholder
                    }
                );
            case 'feature':
                var target_id_input = $(tagArea).attr('id');
                var source_id_values = target_id_input.replace('input', 'values')
                $('#'+target_id_input+'').tagit(
                    {
                        singleField: true,
                        singleFieldNode: $('#'+source_id_values+''),
                        placeholderText: placeholder
                    }
                );
        }
        return this;
    };
})(jQuery);