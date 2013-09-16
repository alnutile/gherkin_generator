(function ($) {

    Drupal.behaviors.gherkin_generator_run = {
        attach: function (context) {
            var setResultsIframe = function(url) {
                $('.test-result').empty();
                var iframe = '<iframe src="' + url + '"';
                iframe += " width='850' height='450' frameborder='0'";
                iframe += " scrolling='no' marginheight='0' marginwidth='0'>";
                iframe += '</iframe>';
                $('.test-result').append(iframe);
            }

            var renderMessage = function(data) {
                if(data.file) {
                  var message = data.file.message;
                  var messages = "<div class='alert alert-info'>";
                  messages += message;
                  messages += "</div>";
                  $('#messages').append(messages);
                }

                if(data.test) {
                    var message = data.test.message;
                    var messages = "<div class='alert alert-info'>";
                    messages += message;
                    messages += "</div>";
                    $('#messages').append(messages);
                    setResultsIframe(data.test.file);
                }
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
                        renderMessage(data);
                }, "json");
            });
        }
    };

})(jQuery);