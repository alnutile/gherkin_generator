<div>
    This is a tool to help to generate
<a href=\"https://github.com/cucumber/cucumber/wiki/Gherkin\" target='_blank'>Gherkin</a>,
a language to aid in software development and testing. The idea came from <a href=\"http://wauat.com/\" target='_blank'>Murrion Sofware</a>.
<br> Just <a href='#' class='btn btn-small btn-info example-test-load'>click here</a> to load an example test.
</div>
<hr>
<ul class="scenario sortable">
    <li class="feature">Feature: Tests for ?</li>
    <li class="name">Scenario: Fill in a name below...</li>
    <li class="url">Given I am on "?"</li>
</ul>


<ul class="hidden example-test scenario sortable ui-sortable">
        <li class="tags"><span class='tag'>@example</span></li>
        <li class="feature">Feature: Example Test for /wiki/Main_Page</li>
        <li class="name">Scenario: WikiPedia</li>
        <li class="url">Given I am on "/wiki/Main_Page"</li>
        <li class="form_field_and_fill_in"><i class="icon-move"> </i>And I fill in "search" with "Behavior Driven Development" <i class="remove icon-remove-circle"></i></li>
        <li class="click_on_type"><i class="icon-move"> </i>And I press "searchButton" <i class="remove icon-remove-circle"></i></li>
        <li class="should_see"><i class="icon-move"> </i>Then I should see "agile software development" <i class="remove icon-remove-circle"></i></li>
        <li class="click_on_type"><i class="icon-move"> </i>And I follow "Donate to Wikipedia" <i class="remove icon-remove-circle"></i></li>
        <li class="should_see"><i class="icon-move"> </i>Then I should see "Thanks" <i class="remove icon-remove-circle"></i></li>
</ul>