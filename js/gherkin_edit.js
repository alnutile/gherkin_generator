/**
 * @todo validation disable button when min requirements are not met on form
 */
(function ($) {

    Drupal.behaviors.gherkin_generator_edit = {
        attach: function (context) {

            var wrapperCheck = function(label_text) {
               if (label_text == 'Given I am on' || label_text.search('Then I') != -1) {
                    return '"';
               } else {
                   return '';
               }
            }

            var closeCheck = function(label_text) {
                if (label_text == 'Given I am on' || label_text.search('Scenario') != -1) {
                    return '';
                } else {
                    return ' <i class="remove icon-remove-circle"></i>';
                }
            }

            var setFeature = function(destination_class, data_value) {
                if(destination_class == 'url') {
                    $('.feature').empty().append('Feature: Tests for ' + data_value);
                }
            }

            var renderMessage = function(message) {
                //@todo pull out error = FALSE/TRUE
                //@todo pull out error type eg error, info, success etc
                var messages = "<div class='alert alert-info'>"+ message + "</div>";
                $('#messages').empty().append(messages);
            }

            var placeSelection = function(text, destination, method, context) {
                console.log("Destination " + destination);
                $(''+destination+'', context)[method](text);
            }

            var remove_icon = '<i class="remove icon-remove-circle"></i>';

            var setTitle = function(destination, text) {
                if(destination == 'name') {
                    $('#edit-title').val(text);
                }
            }

            $('#gherkin-generator-node-form').submit(
                function(e){
                    e.preventDefault();
                }
            );

            $('#edit-run-test').click(function(){
                var scenario = $('.scenario').text();
                $.post('/admin/gherkin_generator/run', { scenario: scenario }, function(data){
                    console.log(data);
                    renderMessage(data.message);
                }, "json");
            });

            $('button.steps', context).click(function(){
                var label = '';
                var label_text = '';

                if($(this).data('test-message')) {
                    label_text = $(this).data('test-message');
                    label += label_text;
                    (label_text == 'Scenario') ? label += ':' : false;
                    label += ' '; //ending space
                }

                //Set the target class
                var destination_class = $(this).data('parent-input');

                //If different target
                //  than existing targets
                if($(this).data('target')) {
                    destination_class = $(this).data('target');
                };

                //Set more uses of this term
                var leaf_class = $(this).data('parent-input');
                var get_value = $(this).data('parent-input');



                //Get Element type an set as needed
                // eg select
                // default is input
                var data_value = '';
                if($(this).data('element-type')) {
                    if($(this).data('element-type') == 'select') {
                        label = $(this).data('test-message') + ' ';
                        label += $('select[name='+get_value+'] :selected').val();
                        data_value = '';
                    }
                } else {
                    var val = $('input[name='+get_value+']').val();
                    setFeature(destination_class, val);
                    data_value += wrapperCheck(label_text);
                    data_value += val;
                    data_value += wrapperCheck(label_text);
                }



                //Setup possible 2nd input and label
                var data_value2 = '';
                var middle_words = '';

                if($(this).data('value-2')) {
                    var get_value2 = $(this).data('value-2');
                    data_value2 += wrapperCheck(label_text);
                    data_value2 += $('input[name='+get_value2+']').val();
                    data_value2 += wrapperCheck(label_text);
                    if($(this).data('middle-words')) {
                        middle_words = $(this).data('middle-words');
                    }
                }

                //Apply elements to the Steps area.
                var destination_wrapper = '<li class="' +leaf_class+ '">'
                    destination_wrapper += label;                       //eg Scenario:
                    destination_wrapper += data_value;                  //The input of the user
                    destination_wrapper += ' ' + middle_words;          //In between text
                    destination_wrapper += ' ' + data_value2;           //More input if applicable
                    destination_wrapper += closeCheck(label_text);
                    destination_wrapper += '</li>';

                var destination = '.scenario .' +destination_class;
                setTitle(destination_class, data_value);
                //Define the method
                //  eg append or replaceWith etc
                var method = $(this).data('method');
                placeSelection(destination_wrapper, destination, method, context);
            });
       }
    };

    //@todo see why on did not work
    // then see why it did not work as a behavior?
    $(document).ready(function() {
        $('i').live('click', function(){
            $(this).parent('li').empty();
        });
    });

})(jQuery);