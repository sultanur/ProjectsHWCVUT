from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.common.exceptions import NoSuchElementException
import time
import string



class TestSearch:
    def __init__(self):
        # path to driver (Firefox)
        self.service = Service(executable_path="./drivers/geckodriver")
        self.driver = webdriver.Firefox(service=self.service)

        self.result_indicator_number: int = 0
        self.paginator_range_label: string = None
        self.elements_job_container = None

    def search_asset_website(self):
        self.driver.get("https://jobs.eaton.com/jobs")
        self.driver.implicitly_wait(2)

        # inserting keyword (C++) into Category of Job Title
        try:
            self.driver.find_element(by=By.ID, value="keyword-search").send_keys("C++")
        except NoSuchElementException:
            print("ERROR: Entered keyword for Job Title  is either incorrect or does not exist")

        #inserting second parameter for searching - Place (Prague)
        try:
            self.driver.find_element(by=By.ID, value="location-search").send_keys("Prague")
        except NoSuchElementException:
            print("ERROR: Entered keyword for Place  is either incorrect or does not exist")

        #Clicking the button to start searching process
        search_button = self.driver.find_element(by=By.ID, value="search-btn")
        search_button.click()

	#wait time for uploading page
        self.driver.implicitly_wait(3)

        #Assertion of the Result Indicator (value is calculated automaticaly for given keyword-parameters)
        try:
            search_result_indicator: string = self.driver.find_element(by=By.ID, value="search-results-indicator")
            result_indicator_number = search_result_indicator.text[0]
            assert (int(result_indicator_number)) == 5
        except NoSuchElementException:
            print("ERROR: No element of search_result_indicator is found\n")

        #Get and compare total number of elements (for given parameters) in job container
        try:
            self.elements_job_container = self.driver.find_elements(by=By.TAG_NAME, value="mat-expansion-panel")
            assert (len(self.elements_job_container) == 5)

            if self.result_indicator_number != 0:
                assert (len(self.elements_job_container) == int(self.result_indicator_number))
        except NoSuchElementException:
            print("ERROR: There are no elements")

        try:
            self.paginator_range_label = self.driver.find_element(by=By.CLASS_NAME, value="mat-paginator-range-label")
            assert (int(self.paginator_range_label.text[4]) == 5)
        except NoSuchElementException:
            print("ERROR: There are no elements")

        time.sleep(10)
        self.driver.quit()


test_search = TestSearch()
test_search.search_asset_website()
