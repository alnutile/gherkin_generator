@javascript
Feature: Making tests and saving files
  Should allow the user to make a test and save a file
  User of the website both anonymous and auth
  The user can come to the site, make a tests and save it

  @anonymous
  Scenario: Anonymous user makes tests and saves it
    Given I am on "/node/add/gherkin-generator"
    And I follow "click here"
    And I press "Save Test"
    Then I wait
    Then I should see "File created"

  @anonymous
  Scenario: User fills in form
    Given I am on "/node/add/gherkin-generator"
    And I fill in "form_field_and_fill_in" with "name"
    And I fill in "field_with_text" with "Hello World"
    And I press "edit-field-text-button"
    And I fill in "field_with_text" with "Goodbye World"
    Then I wait
    Then I should see "Hello World"

  @anonymous
  Scenario: Anonymous user adds 2nd scenario
    Given I am on "/node/add/gherkin-generator"
    And I follow "click here"
    And I should see "Scenario: WikiPedia"
    And I fill in "name" with "Mink Rocks"
    And I press "Name it"
    Then I should see "Scenario: Mink Rocks"
    And I should see "Scenario: WikiPedia"

  @anonymous
  Scenario: Anonymous user adds looks at feil
    Given I am on "/node/add/gherkin-generator"
    Then I should see "This is a tool to help"
    And I follow "click here"
    And I press "Save Test"
    Then I wait
    Then I should see "File created"
    And I follow savedTest
    Then I should see "Scenario: WikiPedia"
    Then I should not see "This is a tool to help"

  @thisone @anonymous
  Scenario: Should be able to add tags to a feature
    Given I am on "/node/add/gherkin-generator"
    Then I should see "Tag"
    And I fill in "feature-tag" with "@tag1"
    Then I should see "@tag1"