<?php

function theme_gherkin_generator_create_file($variables) {
    $scenario = $variables['scenario'];
    $file = '';
    foreach($scenario as $key) {
        $new_line = _gherkin_generator_new_line($key['new_line']);
        $new_line_above = _gherkin_generator_new_line($key['new_line_above']);
        $spaces = _gherkin_generator_spaces($key['spaces']);
        $file = $file . "{$new_line_above}" . "{$spaces}" . $key['string'] . "{$new_line}\r\n";
    }
    return $file;
}



function theme_gherkin_generator_create_html($array) {

}

function template_preprocess_gherkin_generator_view_test(&$variables) {
    $node = menu_get_object();
    $filename = $node->title;
    $file = _gherkin_generator_file_exists($filename);
    if($file) {

        $file_open = fopen($file, "r");
        $file_read = fread($file_open, filesize($file));
        $file_to_array = _gherkin_generator_turn_file_to_array($file_read);
        watchdog('test_file', print_r($file_to_array, 1));
    }
}

function template_preprocess_gherkin_questions_area(&$variables) {

    $variables['features_tags_value'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'features-tagit-values',
        ),
        '#name' => 'features_tag_value',
    );
    $variables['features_tags_input'] = array(
        '#markup' => "<ul id='features-tagit-input'></ul><div class='help-block'>Start each tag with @. Just separate by comma for more than one tags. Tags can not have spaces.</div>"
    );
}