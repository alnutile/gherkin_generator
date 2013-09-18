<?php

function gherkin_generator_save() {
    if(isset($_REQUEST['scenario'])) {
        $response = _gherkin_generator_save_to_file($_REQUEST);

        if($response['file'] != FALSE){
            $results = array('file' => $response);
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
        $response = array('message' => t('Bad Request'), 'file' => FALSE, 'error' => '1');
        drupal_json_output($response);
        exit();
    }
}
