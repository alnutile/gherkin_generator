<?php

/**
 * @todo this needs to not do count but text
 *   since a test can be numerous scenarios
 * @param $scenario
 * @return string
 */
function _gherkin_generator_parse_questions($scenario) {
    //Need to consider what is in each row so I can parse each string and make the output array
    //to then pass to the theme function to output the
    //file.
    $final_output = '';
    $count = 0;
    foreach($scenario as $value) {
        if(gherkin_generator_string_type(trim($value))) {
            $scenario_array[] = gherkin_generator_string_type(trim($value));
        }
//        //Count does not work here since it can be more than one scenario
//        //need to do simple string review eg
//        //Feature or Scenario or Keyword
//        if($count == 1) {
//            $indent = '  ';
//        } elseif($count > 1) {
//            $indent = '    ';
//        } else {
//            $indent = '';
//        }
//        $final_output = $final_output .  $indent . $value . " \r\n";
//        $count ++;
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
function gherkin_generator_string_type($string) {
    $compare = gherkin_generator_string_types();
    foreach($compare as $key) {
        if ($results = $key($string)) {
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
function gherkin_generator_string_feature($string) {
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


function gherkin_generator_string_scenario($string) {
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

function gherkin_generator_string_tags($string) {
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('@');
    drupal_alter('gherkin_generator_string_tags', $options);
    if(in_array($first_word, $options)) {
        return array(
            'string' => $string,
            'spaces' => 0, /* this will really depend on the parent */
            'new_line' => 0
        );
    }
}

function gherkin_generator_string_steps($string) {
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