<?php

/**
 * @todo Generate title from hash of scenerio
 *   until nid exists
 */
function gherkin_generator_run() {
    if(isset($_REQUEST['scenario'])) {
        $response = _gherkin_generator_save_to_file($_REQUEST);

        if($response['file'] != FALSE){
            $run_test_response = _gherkin_generator_run_test($response['file'], $_REQUEST['filename']);
            //@todo responsd to error!
            $results = array('file' => $response, 'test' => $run_test_response);
            drupal_json_output($results);
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

function _gherkin_generator_save_to_file($request) {
    $feature = _gherkin_generator_parse_questions($request['scenario']);
    $filename = $request['filename'];
    $path = file_build_uri("/gherkin_tests/");

    if (!file_prepare_directory($path, FILE_CREATE_DIRECTORY)) {
        drupal_mkdir($path);
    }

    $response = file_unmanaged_save_data($feature, $path . '/' . $filename . '.feature', $replace = FILE_EXISTS_REPLACE);
    $file_url = l('click here', file_create_url($response), array('attributes' => array('target' => '_blank')));

    if($response == FALSE) {
        watchdog('gherkin_generator', "File could not be made.", $variables = array(), $severity = WATCHDOG_ERROR, $link = NULL);
        return array('message' => "Error file could not be save", 'file' => $response);
    } else {
        $date = format_date(time(), $type = 'medium', $format = '', $timezone = NULL, $langcode = NULL);
        watchdog('gherkin_generator', "%date File made %name", $variables = array('%date' => $date, '%name' => $response), $severity = WATCHDOG_NOTICE, $link = $file_url);
        return array('message' => t('@date: <br> File created !name to download ', array('@date' => $date, '!name' => $file_url)), 'file' => $response);
    }
}

function _gherkin_generator_parse_questions($scenario) {
    $final_output = '';
    $count = 0;
    foreach($scenario as $value) {
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
    return $final_output;
}

function _gherkin_generator_run_test($file, $timestamp) {
    if (!is_file($file)) {
        //@todo does this stop the process and feedback the error system if
        //  file does not exist?
        watchdog('gherkin_generator', "Error file does not exist", $variables = array(), $severity = WATCHDOG_ERROR, $link = $file);
        return array('message' => "Error file does not exist", 'file' => $file);
    } else {
        $path = drupal_get_path('module', 'gherkin_generator');
        $absolute_file_path = drupal_realpath($file);

        $path_results = file_build_uri("/gherkin_tests/results");
        if (!file_prepare_directory($path_results, FILE_CREATE_DIRECTORY)) {
            drupal_mkdir($path_results);
        }

        $test_id = $timestamp;
        $results_uri = $path_results . '/' . $timestamp . '.html';              //Need to show the file in iframe later
        $results_url = file_create_url($results_uri);                           //
        $output = drupal_realpath($path_results) . '/' . $test_id . '.html';    //Needed to run bin

        $response = exec("cd $path/behat && bin/behat --format=html --out $output $absolute_file_path && echo $?");
        $date = format_date(time(), $type = 'medium', $format = '', $timezone = NULL, $langcode = NULL);
        if($response == 0) {
            watchdog('gherkin_generator', "%date Test successful results at %name", $variables = array('%date' => $date, '%name' => $output), $severity = WATCHDOG_NOTICE, $link = $file);
            return array('message' => t('@date: <br> Test successful!', array('@date' => $date)), 'file' => $results_url, 'error' => FALSE);
        } else {
            watchdog('gherkin_generator', "%date Error Running Test %name", $variables = array('%date' => $date, '%name' => $file), $severity = WATCHDOG_ERROR, $link = $file);
            return array('message' => t('@date: <br> Error running test !name to download ', array('@date' => $date, '@name' => $file)), 'file' => $file, 'error' => TRUE);
        }
    }
}

