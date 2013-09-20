<?php


function _gherkin_generator_node_form(&$form) {
    $path = drupal_get_path('module', 'gherkin_generator');
    drupal_add_library('system', 'ui.sortable');
    $form['#attached']['css']['gherkin_generator'] = $path . '/css/gherkin_edit.css';
    $form['#attached']['js']['gherkin_generator_tags'] = $path . '/js/gherkin_apply_tags.js';
    $form['#attached']['js']['gherkin_generator_edit'] = $path . '/js/gherkin_edit.js';
    $form['#attached']['js']['gherkin_generator_run'] = $path . '/js/gherkin_run.js';
    $form['#attached']['js']['gherkin_generator_save'] = $path . '/js/gherkin_save.js';

    $filename = REQUEST_TIME;

    $form['title'] = array(
        '#type' => 'hidden',
        '#default_value' => $filename
    );

    $form['actions']['#attributes'] = array('class' => array('hidden'));
    $form['additional_settings']['#type'] = 'fieldset';
    $form['additional_settings']['#attributes'] = array('class' => array('hidden'));

    $form['existing_test'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('well'), 'id' => 'existing-test'),
        '#weight' => -101,
    );

    $form['existing_test']['build'] = array(
        '#theme' => 'gherkin_questions_area'
    );


    $form['existing_test']['actions'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('actions')),
    );


    $form['existing_test']['actions']['run_test'] = array(
        '#type' => 'button',
        '#name' => 'run_test',
        '#value' => t('Run Test'),
        '#attributes' => array('class' => array('btn-success', 'disabled')),
    );

    $form['existing_test']['actions']['save_test'] = array(
        '#type' => 'button',
        '#name' => 'save_test',
        '#value' => 'Save Test',
        '#attributes' => array('class' => array('btn-info')),
    );

    $form['existing_test']['actions']['start_over'] = array(
        '#type' => 'button',
        '#name' => 'start_over',
        '#value' => t('Start Over'),
        '#attributes' => array('class' => array('btn-danger', 'disabled')),
    );

    $form['questions'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('well')),
        '#weight' => -100
    );


    $modules_with_folders = gherkin_generator_check_for_modules();
    $modules_writable = _gherkin_generator_options_list($modules_with_folders);

    if(user_access('save gherkin test')) {
        $form['questions']['save_to'] = array(
            '#type' => 'select',
            '#name' => 'save_to',
            '#options' => $modules_writable,
            '#description' => t('Save file to one of these modules folders'),
            '#validated' => TRUE,
            '#suffix' => '<hr>'
        );
    }

    $form['questions']['test_name']['name'] = array(
        '#type' => 'textfield',
        '#title' => t('What do you want to call this test?'),
        '#attributes' => array('class' => array('span12'), 'placeholder' =>  t('A simple descriptive name of the test')),

    );

    $form['questions']['test_name']['name_button'] = array(
        '#type' => 'button',
        '#value' => t('Name it'),
        '#attributes' => array(
            'data-method' => array('replaceWith'),
            'data-test-message' => array('Scenario'),
            'data-parent-input' => array('name'),
            'class' => array('steps')
        ),
        '#suffix' => '<hr>'
    );


    $form['questions']['when_i_go_to']['url'] = array(
        '#type' => 'textfield',
        '#title' => t('When I go to'),
        '#name' => 'url',
        '#attributes' => array('class' => array('span12'), 'placeholder' =>  t('a full website address')),
    );

    $form['questions']['when_i_go_to']['url_button'] = array(
        '#type' => 'button',
        '#name' => 'go_to',
        '#value' => t('Add'),
        '#attributes' => array(
            'data-method' => array('replaceWith'),
            'data-test-message' => array('Given I am on'),
            'data-parent-input' => array('url'),
            'class' => array('steps')
        ),
        '#suffix' => '<hr>'
    );


    $form['questions']['and_i_fill_in']['form_field_name'] = array(
        '#type' => 'textfield',
        '#title' => t('And I fill in'),
        '#name' => 'form_field_and_fill_in',
        '#attributes' => array('class' => array('span12'), 'placeholder' =>  t('a form field name')),
    );

    $form['questions']['and_i_fill_in']['with'] = array(
        '#markup' => 'with',
        '#prefix' => '<div class="qualifier">',
        '#suffix' => '</div>',
    );

    $form['questions']['and_i_fill_in']['field_text'] = array(
        '#type' => 'textfield',
        '#name' => 'field_with_text',
        '#attributes' => array('class' => array('span12'), 'placeholder' =>  t('with the following text field')),
    );

    $form['questions']['and_i_fill_in']['field_text_button'] = array(
        '#type' => 'button',
        '#name' => 'field_text_add',
        '#value' => t('Add'),
        '#attributes' => array(
            'data-method' => array('append'),
            'data-test-message' => array('And I fill in'),
            'data-parent-input' => array('form_field_and_fill_in'),
            'data-value-2' => array('field_with_text'),
            'data-middle-words' => array('with'),
            'class' => array('steps')
        ),
        '#suffix' => '<hr>'
    );


    $form['questions']['and_i_click_on_a']['click_on_type'] = array(
        '#type' => 'select',
        '#name' => 'click_on_type',
        '#title' => t('And I click on a'),
        '#options' => array('follow' => t('link'), 'press' => t('button')),
        '#validated' => TRUE
    );

    $form['questions']['and_i_click_on_a']['called'] = array(
        '#prefix' => '<div class="qualifier">',
        '#suffix' => '</div>',
        '#markup' => 'called',
    );

    $form['questions']['and_i_click_on_a']['field_text'] = array(
        '#type' => 'textfield',
        '#name' => 'click_on_text',
        '#attributes' => array('class' => array('span12'), 'placeholder' =>  t('enter a link of button name here'))
    );

    $form['questions']['and_i_click_on_a']['click_on_a'] = array(
        '#type' => 'button',
        '#name' => 'click_on_a',
        '#value' => t('Add'),
        '#attributes' => array(
            'data-method' => array('append'),
            'data-element-type' => array('select'),
            'data-target' => array('click_on'),
            'data-test-message' => array('And I'),
            'data-parent-input' => array('click_on_type'),
            'data-value-2' => array('click_on_text'),
            'class' => array('steps')
        ),
        '#suffix' => '<hr>'
    );

    $form['questions']['then_i_should_see']['click_on_type'] = array(
        '#type' => 'select',
        '#name' => 'should_see',
        '#prefix' => '<div class="qualifier">',
        '#suffix' => '</div>',
        '#title' => t('Then I should see'),
        '#options' => array('should see' => t('see'), 'should not see' => t('not see')),
        '#validated' => TRUE
    );

    $form['questions']['then_i_should_see']['see_not_see_some_text'] = array(
        '#type' => 'textfield',
        '#name' => 'see_not_see_some_text',
        '#attributes' => array('class' => array('span12'), 'placeholder' =>  t('some text on that page'))
    );

    $form['questions']['then_i_should_see']['see_not_see'] = array(
        '#type' => 'button',
        '#name' => 'see_not_see',
        '#value' => t('Add'),
        '#attributes' => array(
            'data-method' => array('append'),
            'data-target' => array('see'),
            'data-element-type' => array('select'),
            'data-test-message' => array('Then I'),
            'data-parent-input' => array('should_see'),
            'data-value-2' => array('see_not_see_some_text'),
            'class' => array('steps')
        ),
        '#suffix' => '<hr>'
    );

    $form['filename'] = array(
        '#type' => 'hidden',
        '#name' => 'filename',
        '#value' => $filename,
    );
}