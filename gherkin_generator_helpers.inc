<?php


/**
 * @param $request
 *   this is an array keyed as such
 *     scenario - an array of the scenario lines one line = one array row
 *     filename -
 * @return array
 */
function _gherkin_generator_save_html_to_file($request) {
    //@todo why was this not loaded with info file files[] call?
    module_load_include('inc', 'gherkin_generator', 'inc/gherkin_generator_file_parsing');
    $scenario_array = _gherkin_generator_parse_questions($request['scenario']);
    $feature = theme('gherkin_generator_create_file', $vars = array('scenario' => $scenario_array));
    $filename = $request['filename'] . '.feature';
    $module = $request['path'];
    global $user;
    //@todo DRY this up for either type of user and repsonse
    if (user_access('save gherkin test')) {
        /* Derived from features.admin.inc module */
        $output = _gherkin_generator_process_file_in_module_folder($module, $filename, $feature, $request);
        return $output;
    } else {
        $output = _gherkin_generator_process_file_in_tmp($filename, $feature);
        return $output;
    }
}


function _gherkin_generator_process_file_in_module_folder($module, $filename, $feature, $request) {
    $full_path = _gherkin_save_path($module);
    $response = file_put_contents("{$full_path}/{$filename}", $feature);
    if($response == FALSE) {
        watchdog('gherkin_generator', "File could not be made.", $variables = array(), $severity = WATCHDOG_ERROR, $link = NULL);
        $output = array('message' => "Error file could not be save", 'file' => $response, 'error' => '1');
    } else {
        $gherkin_linkable_path = _gherkin_linkable_path($request['path'], $filename);
        $url = url($gherkin_linkable_path, $options = array('absolute' => TRUE));
        $file_url = l('click here', $url, array('attributes' => array('target' => '_blank', 'id' => array('test-file'))));
        $date = format_date(time(), $type = 'medium', $format = '', $timezone = NULL, $langcode = NULL);
        watchdog('gherkin_generator', "%date File made %name", $variables = array('%date' => $date, '%name' => $filename), $severity = WATCHDOG_NOTICE, $link = $file_url);
        $output =  array('message' => t('@date: <br> File created !name to download ', array('@date' => $date, '!name' => $file_url)), 'file' => $gherkin_linkable_path, 'error' => '0');
    }

    return $output;
}

function _gherkin_generator_process_file_in_tmp($filename, $feature) {
    $path = file_build_uri("/gherkin_tests/");
    $response = file_unmanaged_save_data($feature, $path . '/' . $filename, $replace = FILE_EXISTS_REPLACE);
    if($response == FALSE) {
        watchdog('gherkin_generator', "File could not be made.", $variables = array(), $severity = WATCHDOG_ERROR, $link = NULL);
        $output = array('message' => "Error file could not be save", 'file' => $response, 'error' => '1');
    } else {
        $file_uri = $response;
        $file_url = l('click here', file_create_url($response), array('attributes' => array('target' => '_blank', 'id' => array('test-file'))));
        $date = format_date(time(), $type = 'medium', $format = '', $timezone = NULL, $langcode = NULL);
        watchdog('gherkin_generator', "%date File made %name", $variables = array('%date' => $date, '%name' => $response), $severity = WATCHDOG_NOTICE, $link = $file_url);
        $output = array('message' => t('@date: <br> File created !name to download ', array('@date' => $date, '!name' => $file_url)), 'file' => $file_uri, 'error' => '0');
    }
    return $output;
}


/**
 * if user is not logged in or not allowed
 * to save file to the module folder
 * I want to save it in the drupal files
 * folder / gherkin_tests folder
 * later I want to clean this of feature files
 */
function _gherkin_generator_temp_folder() {
    $path = file_build_uri("/gherkin_tests/");

    if (!file_prepare_directory($path, FILE_CREATE_DIRECTORY)) {
        drupal_mkdir($path);
    }

}

function _gherkin_linkable_path($module, $filename) {
    $module_path = drupal_get_path('module', $module);
    return $module_path . '/' . GHERKIN_FOLDER . '/' . $filename;
}

/**
 * @todo this needs to consider non root as well
 *   eg anonymous user saves to tmp while test run?
 *   or to allow them to link to it.
 */
function _gherkin_save_path($module) {
    $module_path = drupal_get_path('module', $module);
    return  DRUPAL_ROOT . '/' . $module_path . '/' . GHERKIN_FOLDER;
}

/**
 * @param $modules
 *  what modules have gherkin_folders
 *  from _gherkin_generator_has_folder()
 * @param $writable
 *  filter out writeable
 *
 * @return
 *  array of modules with folder
 */
function _gherkin_generator_options_list($module, $writable = TRUE) {
    $options = array();
    foreach($module as $key => $value) {
        $nice_name = $module[$key]['nice_name'];
        if($writable == TRUE) {
            ($module[$key]['writable'] == 1) ? $options[$key] = $nice_name : '';
        } else {
            $options[$key] = $nice_name;
        }
    }
    return $options;
}


function _gherkin_generator_has_folder($module) {
    $status = array();
    $path = drupal_get_path('module', $module);
    $full_path = $path . '/' . GHERKIN_FOLDER;
    if(drupal_realpath($full_path)) {
        $status['exists'] = TRUE;
        $status['writable'] = (is_writeable($full_path)) ? TRUE : FALSE;
        $nice_name = system_rebuild_module_data();
        $status['nice_name'] = $nice_name[$module]->info['name'];

        return $status;
    }
}



function _gherkin_generator_new_line($new_line) {
    if($new_line == 1) {
        return "\r\n";
    } else {
        return "";
    }
}

function _gherkin_generator_spaces($spaces) {
    $spaces_return = '';
    for($i = 0; $i <= $spaces; $i++) {
        $spaces_return = $spaces_return . " ";
    }
    return $spaces_return;
}

function _gherkin_generator_get_module_name_from_file_name($filename) {
    $file_array = explode('_', $filename);
    $folder = array_slice($file_array, 0, -1);
    $module = implode('_', $folder);
    return $module;
}

function _gherkin_generator_get_system_path_to_file($filename) {
    $module = _gherkin_generator_get_module_name_from_file_name($filename);
    $path = drupal_get_path('module', $module);
    $full_relative_path = $path . '/' . GHERKIN_FOLDER . '/';
    $system_path = drupal_realpath($full_relative_path);
    return $system_path;
}

function _gherkin_generator_file_exists($filename) {
    $system_path = _gherkin_generator_get_system_path_to_file($filename);
    watchdog("file_exists", $system_path);
    $absolute_path = $system_path . '/' . $filename . '.feature';
    if(is_file($absolute_path)) {
        return $absolute_path;
    } else {
        return FALSE;
    }
}

function _gherkin_generator_turn_file_to_array($file) {
    $array = explode("\n", $file);
    foreach($array as $key => $value) {
        if(strlen($value) <= 1) {
            unset($array[$key]);
        }
    }
    return $array;
}