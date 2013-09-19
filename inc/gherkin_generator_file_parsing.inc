<?php

/**
 * @todo this needs to not do count but text
 *   since a test can be numerous scenarios
 * @param $scenario
 * @return string format of file
 */
function _gherkin_generator_parse_questions($scenario) {
    $scenario_array = array();
    $count = 0; /* used to get tags */
    foreach($scenario as $value) {
        if($results = gherkin_generator_string_type(trim($value), $scenario, $count)) {
            //@todo DRY this up of separate
            watchdog('test_results', print_r($results, 1));
            watchdog('test_results_count', count($results));
            if(count($results) < 3) {
                foreach($results as $row) {
                    if($row) {
                        $scenario_array[] = $row;
                    }
                }
            } else {
                $scenario_array[] = $results;
            }
        }
        $count++;
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
function gherkin_generator_string_type($string, $scenario, $count) {
    $compare = gherkin_generator_string_types();
    foreach($compare as $key) {
        if ($results = $key($string, $scenario, $count)) {
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
    $options = array('gherkin_generator_string_feature', 'gherkin_generator_string_scenario', 'gherkin_generator_string_steps');
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
function gherkin_generator_string_feature($string, $scenario, $count) {
    $results = array();
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('Feature:');
    drupal_alter('gherkin_generator_string_feature', $options);
    if(in_array($first_word, $options)) {
        if($result = gherkin_generator_string_tags($scenario, $count - 1, 0)) {
            $results[] = $result;
        }

        $results[] = array(
            'string' => $string,
            'spaces' => 0,
            'new_line' => 0,
            'new_line_above' => 0,
        );

        return $results;
    }
}


function gherkin_generator_string_scenario($string, $scenario, $count) {
    $results = array();
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('Scenario:');
    drupal_alter('gherkin_generator_string_feature', $options);
    if(in_array($first_word, $options)) {
        if($result = gherkin_generator_string_tags($scenario, $count - 1, 2)) {
            $results[] = $result;
        }
        $results[] = array(
            'string' => $string,
            'spaces' => 2,
            'new_line' => 0,
            'new_line_above' =>  ($result) ? 0 : 1,
        );
        return $results;
    }
}

function gherkin_generator_string_tags($scenario, $count, $spaces = 0) {
    if(array_key_exists($count, $scenario)) {
        $string = $scenario[$count];
        $first_word = _gherkin_generator_pop_first_word($string);
        $options = array('@');
        drupal_alter('gherkin_generator_string_tags', $options);
        foreach($options as $key => $value) {
            if(strpos($first_word, $value) !== false) {
                $string = str_replace(',', ' ', $string);
                return array(
                    'string' => $string,
                    'spaces' => $spaces,
                    'new_line' => 0,
                    'new_line_above' => ($count > 1) ? 1 : 0,
                );
            }
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