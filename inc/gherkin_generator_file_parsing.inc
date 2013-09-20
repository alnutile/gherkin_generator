<?php

/**
 * @todo this needs to not do count but text
 *   since a test can be numerous scenarios
 * @param $scenario
 * @param $direction eg to html or to file format
 * @return string format of file
 */
function _gherkin_generator_parse_questions($scenario, $direction = 'file') {
    $scenario_array = array();
    $count = 0; /* used to get tags */
    foreach($scenario as $value) {
        if($results = gherkin_generator_string_type(trim($value), $scenario, $count, $direction)) {
            //@todo DRY this up of separate
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
    return $scenario_array;
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
function gherkin_generator_string_type($string, $scenario, $count, $direction) {
    $compare = gherkin_generator_string_types();
    foreach($compare as $key) {
        if ($results = $key($string, $scenario, $count, $direction)) {
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
function gherkin_generator_string_feature($string, $scenario, $count, $direction) {
    $results = array();
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('Feature:');
    drupal_alter('gherkin_generator_string_feature', $options);
    if(in_array($first_word, $options)) {
        switch($direction) {
            case 'file':
                if($result = gherkin_generator_string_tags($scenario, $count - 1, 0, $direction)) {
                    $results[] = $result;
                }
                $results[] = array(
                    'string' => $string,
                    'spaces' => 0,
                    'new_line' => 0,
                    'new_line_above' => 0,
                );
            case 'html_view':
                if($result = gherkin_generator_string_tags($scenario, $count - 1, 0, $direction)) {
                    $results[] = $result;
                }
                $results[] = array(
                    'data' => $string,
                    'class' => array('feature', "spaces-none")
                );
        }
        watchdog('test_feature_result', print_r($results[0], 1));
        return $results;
    }
}


function gherkin_generator_string_scenario($string, $scenario, $count, $direction) {
    $results = array();
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('Scenario:');
    drupal_alter('gherkin_generator_string_feature', $options);
    if(in_array($first_word, $options)) {
        switch($direction) {
            case 'file':
                if($result = gherkin_generator_string_tags($scenario, $count - 1, 2, $direction)) {
                    $results[] = $result;
                }
                $results[] = array(
                    'string' => $string,
                    'spaces' => 2,
                    'new_line' => 0,
                    'new_line_above' =>  ($result) ? 0 : 1,
                );
            case 'html_view':
                if($result = gherkin_generator_string_tags($scenario, $count - 1, 2, $direction)) {
                    $results[] = $result;
                }
                $results[] = array(
                    'data' => $string,
                    'class' => array('scenario', "spaces-two")
                );
        }
        return $results;
    }
}

function gherkin_generator_string_tags($scenario, $count, $spaces = 0, $direction) {

    if(array_key_exists($count, $scenario)) {
        $string = $scenario[$count];
        $options = array('@');
        drupal_alter('gherkin_generator_string_tags', $options);
        foreach($options as $key => $value) {
            if(strpos($string, $value) !== false) {
                switch($direction) {
                case 'file':
                        $string = str_replace(',', ' ', $string);
                        return array(
                            'string' => $string,
                            'spaces' => $spaces,
                            'new_line' => 0,
                            'new_line_above' => ($count > 1) ? 1 : 0,
                        );
                case 'html_view':
                    $results = array(
                        'data' => $string,
                        'class' => array('tags', "spaces-$spaces")
                    );
                    return $results;
                }
            }
        }
    }
}

function gherkin_generator_string_steps($string, $parent, $count, $direction) {
    $first_word = _gherkin_generator_pop_first_word($string);
    $options = array('Given', 'When', 'Then', 'And', 'But');
    drupal_alter('gherkin_generator_string_steps', $options);
    if(in_array($first_word, $options)) {
        switch($direction) {
            case 'file':
              return array(
                'string' => $string,
                'spaces' => 4,
                'new_line' => 0,
                'new_line_above' => 0
            );
            case 'html_view':
                $results[] = array(
                    'data' => $string,
                    'class' => array('steps', "spaces-four")
                );
                return $results;
        }
    }
}

function _gherkin_generator_pop_first_word($string) {
    $first_word = explode(' ', $string);
    return array_shift($first_word);
}


function _gherkin_generator_output_html_line($line) {
    $first_word = _gherkin_generator_pop_first_word($line);

    return array('data' => $line, 'class' => array('test'));
}