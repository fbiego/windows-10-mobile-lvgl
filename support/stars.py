import requests
import os
import time

Import("env")

print("pre build scripts - stars.h")

# GitHub repository details
REPO_NAME = 'windows-10-mobile-lvgl'


# GitHub API endpoint for stargazers
API_URL = f'https://api.github.com/repos/fbiego/{REPO_NAME}/stargazers'

def fetch_all_stargazers(api_url):
    stargazers = []
    while api_url:
        response = requests.get(api_url, headers={'Accept': 'application/vnd.github.v3+json'})
        stargazers.extend(response.json())
        # Check if there is a 'next' page
        if 'Link' in response.headers:
            links = response.headers['Link'].split(', ')
            next_link = None
            for link in links:
                if 'rel="next"' in link:
                    next_link = link[link.find('<')+1:link.find('>')]
                    break
            api_url = next_link
        else:
            api_url = None
    return stargazers


def generate_list(path):
    try:
        # Fetch all stargazers
        stargazers = fetch_all_stargazers(API_URL)

        # Sort stargazers alphabetically by username
        stargazers_sorted = sorted(stargazers, key=lambda user: user['login'])


        list_users = ""
        image = ""

        for user in stargazers_sorted:
            list_users = list_users + "{\"" + user['login'] + "\",  &ui_img_stars_ic_png}," + "\n\t"



        # Readme template
        stars_h_template = f"""
#ifndef _STARS_H
#define _STARS_H

#ifdef __cplusplus
extern "C" {{
#endif

// This file is generated using stars.py which fetches the current stargazers of this repository

#include "ui_common.h"

// TODO (add github avatars) default: ui_img_stars_ic_png
user_info_t users[] = {{
    {list_users}
}};

#ifdef __cplusplus
}} /*extern "C"*/
#endif

#endif


"""

        # Write to stars.h
        with open(path, 'w') as header_file:
            header_file.write(stars_h_template)

        print("stars.h has been updated with the list of stargazers.")

    except:
        print("failed to update stars.h")


file_path = "src/ui/stars.h"

if os.path.exists(file_path):
    current_time = time.time()

    last_modified = os.path.getmtime(file_path)
    hours_diff = (current_time - last_modified) / 3600
    if (hours_diff > 24):
        generate_list(file_path)
    else:
        print(f"stars.h already modified {round(hours_diff, 2)} hrs ago")
else:
    print("stars.h doesn't exist")
    generate_list(file_path)