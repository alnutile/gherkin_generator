<?php

/**
 * @todo this needs to not do count but text
 *   since a test can be numerous scenarios
 * @param $scenario
 * @return string format of file
 */
function _gherkin_generator_parse_questions($scenario) {
    $scenario_array = array();
    foreach($scenario as $value) {
        if($results = gherkin_generator_string_type(trim($value), $scenario_array)) {
            $scenario_array[] = $results;
        }
    }
    $output = theme('gherkin_generator_create_file', $vars = array('scenario' => $scenario_array));
    return $output;
}


/**
 * @param $string
 *   The row in the gherkin test to review
 *   and decide what place it fits in the gherkin file.
 * @return the array as needed
 *   string
 *   spaces
 *   new_line
 */
function gherkin_generator_string_type($string, $parent) {
    $compare = gherkin_generator_string_types();
    foreach($compare as $key) {
        if ($results = $key($string, $parent)) {
            return $results;
        }
    }
}

/**
 * Breaking this true false parts into separate functions
 * Later we can consider other string values to check for
 * as well as add different languages that gherkin supports.
 */

function gherkin_generator_string_types() {
    $options = array('gherkin_generator_string_feature', 'gherkin_generator_string_scenario', 'gherkin_generator_string_tags', 'gherkin_generator_string_steps');
    drupal_alter('gherkin_generator_string_types', $options);
    return $options;
}

/**
 * @param $string
 * Features should have trailing lines
 * 1. The benefits
 * 2. The role of the user
 * 3. The description
 * @return array
 */
function gherkin_generator_string_feature($string, $parent) {
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('Feature:');
    drupal_alter('gherkin_generator_string_feature', $options);
    if(in_array($first_word, $options)) {
        return array(
            'string' => $string,
            'spaces' => 0,
            'new_line' => 1
        );
    }
}


function gherkin_generator_string_scenario($string, $parent) {
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('Scenario:');
    drupal_alter('gherkin_generator_string_scenario', $options);
    if(in_array($first_word, $options)) {
        return array(
            'string' => $string,
            'spaces' => 2,
            'new_line' => 0
        );
    }
}

function gherkin_generator_string_tags($string, $parent) {
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('@');
    drupal_alter('gherkin_generator_string_tags', $options);

    foreach($options as $key => $value) {
        if(strpos($first_word, $value) !== false) {
            return array(
                'string' => $string,
                'spaces' => (empty($parent)) ? 0 : 2, /* empty means Feature level else Scenario */
                'new_line' => 0
            );
        }
    }
}

function gherkin_generator_string_steps($string, $parent) {
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('Given', 'When', 'Then', 'And', 'But');
    drupal_alter('gherkin_generator_string_steps', $options);
    if(in_array($first_word, $options)) {
        return array(
            'string' => $string,
            'spaces' => 4,
            'new_line' => 0
        );
    }
}

function _gherkin_generator_pop_first_word($string) {
    $first_word = explode(' ', $string);
    return array_shift($first_word);
}