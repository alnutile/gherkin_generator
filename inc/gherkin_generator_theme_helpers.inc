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
    module_load_include('inc', 'gherkin_generator', 'inc/gherkin_generator_file_parsing');
    $node = menu_get_object();
    $filename = $node->title;
    $file = _gherkin_generator_file_exists($filename);
    $output = '';
    $items = array();
    if($file) {
        $file_open = fopen($file, "r");
        $file_read = fread($file_open, filesize($file));
        $file_to_array = _gherkin_generator_turn_file_to_array($file_read);
        $array_to_html_array = _gherkin_generator_parse_questions($file_to_array, $direction = 'html_view');
        $output = theme('item_list', $vars = array('items' => $array_to_html_array, 'attributes' => array('class' => array('scenario'))));
    } else {
        $output = "Could not find the related file";
    }

    $variables['actions'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('actions')),
    );

    $variables['actions']['run_button'] = array(
        '#type' => 'button',
        '#name' => 'run_test',
        '#value' => t('Run Test'),
        '#attributes' => array('class' => array('view-mode', 'btn-success'))
    );

    $variables['filename'] = array(
        '#type' => 'hidden',
        '#value' => $node->title,
        '#name' => 'filename',
    );

    $variables['questions_view'] = $output;
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