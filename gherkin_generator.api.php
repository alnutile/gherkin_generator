<?php

/**
 * @file
 * Hooks provided by the Gherkin Generator module.
 */

/**
 * By placing your tests in your modules gherkin_features folder
 * The gherkin_gererator module will pick them up and allow you to
 * choose that module as a place to store your generated tests.
 * This will also help the behat_admin module to find your tests.
 * Make sure the folder is writable if you would like the gerkin_generator
 * to write to it.
 *
 * You can read up on the formatting at @link http://behat.org/ @endlink
 *
 * Example:
 * @code
 *
 * @code
 * @example_feature_tag
 * Feature: Example Test for /wiki/Main_Page
 *   @example_scenario_tag
 *   Scenario: WikiPedia
 *     Given I am on "/wiki/Main_Page"
 *     And I fill in "search" with "Behavior Driven Development"
 *     And I press "searchButton"
 *     Then I should see "agile software development"
 *     And I follow "Donate to Wikipedia"
 *     Then I should see "Thanks"
 * @endcode
 *
 *
 */
