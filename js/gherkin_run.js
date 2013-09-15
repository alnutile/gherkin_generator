(function ($) {

    Drupal.behaviors.gherkin_generator_run = {
        attach: function (context) {
            var renderMessage = function(message) {
                var messages = "<div class='alert alert-info'>";                //@todo pull out error = FALSE/TRUE
                messages += message;                                            //@todo pull out error type eg error, info, success etc
                messages += "</div>";
                $('#messages').empty().append(messages);
            };

            $('#edit-run-test').click(function(){
                var scenario = $('ul.scenario li');
                var items = scenario.length;
                var scenario_array = new Array()
                for(var i = 0; i < items; i++) {
                    scenario_array[i] =$(scenario[i]).text();
                }

                var filename = $('input[name=filename]').val();
                console.log("Filename" + filename);
                var parameters = {
                    "scenario[]": scenario_array,
                    "filename": filename
                };
                $.post('/admin/gherkin_generator/run', parameters, function(data){
                        console.log(data);
                        renderMessage(data.message);
                }, "json");
            });
        }
    };

})(jQuery);