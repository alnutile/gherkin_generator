<?php

/**
 * @todo Generate title from hash of scenerio
 *   until nid exists
 */
function gherkin_generator_run() {
    if(isset($_REQUEST['scenario'])) {
        $response = _gherkin_generator_save_to_file($_REQUEST['scenario']);
        if($response['file'] != FALSE){
            //Run the tests
            drupal_json_output($response);
            exit();
        } else {
            //Send back the Error
            drupal_json_output($response);
            exit();
        }
    } else {
        //Send back the Error
        watchdog('gherkin_generator', "Bad Request", $variables = array(), $severity = WATCHDOG_ERROR, $link = NULL);
        $response = array('message' => t('Bad Request'), 'file' => FALSE);
        drupal_json_output($response);
        exit();
    }
}

function _gherkin_generator_save_to_file($scenario) {
    $feature = _gherkin_generator_parse_questions($scenario);
    //watchdog('returned_features', print_r($feature, 1));
    $path = file_build_uri("/gherkin_tests/");

    if (!file_prepare_directory($path, FILE_CREATE_DIRECTORY)) {
        drupal_mkdir($path);
    }

    $response = file_unmanaged_save_data($feature, $path . '/test.feature', $replace = FILE_EXISTS_REPLACE);

    if($response == FALSE) {
        watchdog('gherkin_generator', "File could not be made.", $variables = array(), $severity = WATCHDOG_ERROR, $link = NULL);
        return array('message' => "Error file could not be save", 'file' => $response);
    } else {
        $date = format_date(time(), $type = 'medium', $format = '', $timezone = NULL, $langcode = NULL);
        watchdog('gherkin_generator', "%date File made %name", $variables = array('%date' => $date, '%name' => $response), $severity = WATCHDOG_NOTICE, $link = $response);
        return array('message' => t('@date: <br> File @name created', array('@date' => $date, '@name' => $response)), 'file' => $response);
    }
}

function _gherkin_generator_parse_questions($scenario) {
    $final_output = '';
    $count = 0;
    foreach($scenario as $value) {
        watchdog('array', print_r($value, 1));
        if($count == 1) {
            $indent = '  ';
        } elseif($count > 1) {
            $indent = '    ';
        } else {
            $indent = '';
        }
        $final_output = $final_output .  $indent . $value . " \r\n";
        $count ++;
    }
    watchdog('final_output', $final_output);
    return $final_output;
}