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
                        console.log("submit form")
                        $('form#gherkin-generator-node-form').submit();
                    }
                }
            };

            $('#edit-save-test').click(function(){
                var scenario = $('ul.scenario:eq(0) li');
                var items = scenario.length;
                var scenario_array = new Array()
                for(var i = 0; i < items; i++) {
                    scenario_array[i] = $(scenario[i]).text();
                }

                var filename = $('input[name=filename]').val();
                console.log("File name" + filename);
                var parameters = {
                    "scenario[]": scenario_array,
                    "filename": filename
                };

                $.post('/admin/gherkin_generator/save', parameters, function(data){
                    renderMessage(data);
                }, "json");
            });
        }
    };

})(jQuery);