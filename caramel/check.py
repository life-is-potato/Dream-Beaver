import requests
from bs4 import BeautifulSoup

def get_most_recent_formations():
    # Send GET request to the website
    url = "https://www.my-mooc.com/fr/categorie/programmation"
    response = requests.get(url)
    if response.status_code != 200:
        print("Failed to fetch website:", response.status_code)
        return []

    # Parse the HTML content
    soup = BeautifulSoup(response.content, "html.parser")

    # Find all formation items
    formation_items = soup.find_all("div", class_="produit-item")

    # Extract formation information
    formations = []
    for item in formation_items:
        # Extract formation name
        formation_name = item.find("div", class_="produit-item__title")
        if formation_name:
            formation_name = formation_name.text.strip()

        # Extract start date
        start_date = item.find("div", class_="produit-item__details__items").find("span")
        if start_date:
            start_date = start_date.text.strip()

        # Add formation to the list
        if formation_name and start_date:
            formations.append({"name": formation_name, "start_date": start_date})

    return formations

if __name__ == "__main__":
    # Get the most recent formations
    recent_formations = get_most_recent_formations()
    if recent_formations:
        print("Most Recent Formations:")
        for formation in recent_formations:
            print("Formation Name:", formation["name"])
            print("Start Date:", formation["start_date"])
            print()
    else:
        print("No formations found or error occurred.")
