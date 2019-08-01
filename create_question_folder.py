#!/usr/bin/env python3

import requests
import shutil


def create_question_template():
    question_number = int(input('Please input question number: '))
    # response = requests.get('https://leetcode.com/api/problems/all/')
    # deal with GFW
    response = requests.get('https://leetcode.com/api/problems/all/', proxies={
        'http': 'http://127.0.0.1:1080',
        'https': 'http://127.0.0.1:1080',
    })
    questions = response.json()['stat_status_pairs']
    question = [question for question in questions if question['stat']['question_id'] == question_number]
    if not question:
        print('question for number %s not found.' % question_number)
        return

    question = question[0]
    question_id = question['stat']['question_id']
    question_title = question['stat']['question__title']
    question_title_slug = question['stat']['question__title_slug']

    print('=== Question Info ===')
    print('ID: %d' % question_id)
    print('Title: %s' % question_title)
    print('Title Slug: %s' % question_title_slug)
    print('Is this correct(Y/n):')
    yes_or_no = input()
    while yes_or_no not in ['y', 'Y', 'n', 'N', '']:
        yes_or_no = input('enter Y or N')
    if yes_or_no in ['n', 'N']:
        print('question incorrect, may need create project mannually.')
        print('exiting...')
        return

    # TODO: get question code snippet
    project_name = '%d-%s' % (question_id, question_title_slug)
    shutil.copytree('template', project_name)
    replace_file_string(project_name + '/README.md', 'QUESTION_TITLE_PLACEHOLDER', question_title)
    replace_file_string(project_name + '/README.md', 'QUESTION_URL_PLACEHOLDER',
                        'https://leetcode.com/problems/%s/' % question_title_slug)
    replace_file_string(project_name + '/CMakeLists.txt', 'PROJECT_NAME_PLACEHOLDER', project_name)
    replace_file_string(project_name + '/main.cc', 'TEST_CASE_NAME_PLACEHOLDER', question_title)
    with open('CMakeLists.txt', 'a') as f:
        f.write('add_subdirectory(%s)\n' % project_name)


def replace_file_string(file_path, placeholder, value):
    with open(file_path, 'r') as f:
        file_data = f.read()
    file_data = file_data.replace(placeholder, value)
    with open(file_path, 'w') as f:
        f.write(file_data)


if __name__ == '__main__':
    create_question_template()
