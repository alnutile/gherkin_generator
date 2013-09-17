(function ($) {
    $( document ).ajaxStart(
        function(){
            $('.saving-tests').fadeIn();
        }
    );

    $( document ).ajaxStop(
        function(){
            $('.saving-tests').fadeOut();
        }
    );

    Drupal.behaviors.gherkin_generator_save = {
        attach: function (context) {

            var renderMessage = function(data) {
                if(data.file) {
                    var message = data.file.message;
                    var messages = "<div class='alert alert-info'>";
                    messages += message;
                    messages += "</div>";
                    $('#messages').append(messages);

                    if(data.file.error == 0) {
                        //$('form#gherkin-generator-node-form').submit();
                    }
                }
            };

            $('#edit-save-test').click(function(){
                if(!$(this).hasClass('disabled')) {
                    var scenario = $('ul.scenario:eq(0) li');
                    var items = scenario.length;
                    var scenario_array = new Array()
                    for(var i = 0; i < items; i++) {
                        scenario_array[i] = $(scenario[i]).text();
                    }
                    if($('#edit-save-to').length == 1) {
                        var path = $('#edit-save-to option:selected').val();
                    } else {
                        var path = Drupal.settings.gherkin_generator.gherkinGeneratorDefaultPath;
                    }
                    var filename = $('input[name=filename]').val();
                    var parameters = {
                        "scenario[]": scenario_array,
                        "filename": filename,
                        "path": path
                    };

                    $.post('/admin/gherkin_generator/save', parameters, function(data){
                        renderMessage(data);
                    }, "json");
                }
            });
        }
    };

})(jQuery);