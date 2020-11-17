import wikipedia
import pickle
import time
import re

if 'hy' in wikipedia.languages():
    print ('ARMENIA')
wikipedia.set_lang("hy")

queue = pickle.load( open( "queue.p", "rb" ) )
visited = pickle.load( open( "visited.p", "rb" ) )

print ('queue size:', len(queue))
print ('visited size:', len(visited))

num_pages_processed = 0

def process_and_save(content, title):
    try:
        content = re.sub('[\n]', ' ', content)
        #content = re.sub('[=’:`)(,.՞»«―՝։՜]', '', content)
        content = ' '.join((content.lower()).split())
        file_name = 'arm_wiki_data_5/{0}'.format(title)
        f = open(file_name, "w")
        n = f.write(content)
        f.close()
    except:
        print('Exception in process_and_save')
        return

skip = False
wiki_page = None
while len(queue) > 0:
    title = queue.pop()
    visited.add(title)
    print('it{0}: Processing {1}...'.format(num_pages_processed, title))
    time.sleep(2)
    try:
        wiki_page = wikipedia.page(title=title)
        process_and_save(wiki_page.content, title)
        for wiki_link in wiki_page.links:
            if not wiki_link in visited and not wiki_link in queue:
                queue.add(wiki_link)
    except:
        print('it{0}: Exception cached for {1}'.format(num_pages_processed,title))
        skip = True

    if skip:
        skip = False
        continue
    if num_pages_processed % 37 == 0:
        print('\tit{0}: len(visited) = {1}'.format(num_pages_processed, len(visited)))
        print('\tit{0}: len(queue) = {1}'.format(num_pages_processed, len(queue)))
        print('\tit{0}: save visited titles ...'.format(num_pages_processed))
        with open('visited.p', 'wb') as fp:
                pickle.dump(visited, fp)
        with open('queue.p', 'wb') as fp:
                pickle.dump(queue, fp)
    num_pages_processed += 1
