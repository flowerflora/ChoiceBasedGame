#include <iostream>
#include <vector>
#include <string>
#include "Load.hpp"
struct Script{
struct Choice{
    std::string text;
    int next;
};
struct Storypoint {
    std::string text;
    int image;
    std::vector<Choice> choices;
};
std::vector<std::string> backgrounds;

std::vector<Storypoint> storyPoints = {
    {
        // Scene 0: Introduction
        "You are a mechanic living in a forest surrounded by mechanical animals. Today, you notice Rusty, your loyal mechanical dog, is not functioning well.\nWhat do you do?",
        0,
        {
            {"Examine Rusty to try to fix him", 1},
            {"Ignore Rusty and continue with your day", 2}
        }
    },
    {
        // Scene 1: Examining Rusty
        "You examine Rusty closely. His gears are worn, and no matter what you try, nothing seems to restore his vitality.\nWhat do you do next?",
        1,
        {
            {"Keep trying to fix Rusty", 3},
            {"Decide to find the original creator", 4},
            {"Wait and hope Rusty will recover on his own", 5}
        }
    },
    {
        // Scene 2: Ignore Rusty
        "You ignore Rusty and go about your day. But you can't shake the feeling that something's wrong.\nDo you go back to him?",
        2,
        {
            {"Yes, go back to check on Rusty", 1},
            {"No, continue with your day", 5}
        }
    },
    {
        // Scene 3: Unable to Fix Rusty
        "Despite your best efforts, Rusty cannot be repaired. His joints squeak, his gears grind, and his once bright eyes have dimmed.\nDo you seek help from the original creator?",
        3,
        {
            {"Yes, leave the forest with Rusty", 4},
            {"No, stay and try to fix him again later", 5}
        }
    },
    {
        // Scene 4: Start the Journey
        "You decide to leave the forest with Rusty in search of the original creator. As you travel, you encounter a mechanical chick flapping frantically but unable to fly due to its tiny metal wings.\nWhat do you do?",
        4,
        {
            {"Help the bird", 6},
            {"Leave the bird and move on", 7}
        }
    },
    {
        // Scene 5: Rusty Weakens Further
        "You put off fixing Rusty. Time passes, and his condition worsens. His movements become slower, his spark fades. You feel a deep sense of guilt.\nDo you reconsider finding the original creator?",
        5,
        {
            {"Yes, leave the forest with Rusty", 4},
            {"No, accept that Rusty is beyond saving", 8}
        }
    },
    {
        // Scene 6: Helping the Bird
        "You stop to help the bird. After some effort, you managed to adjust its design to allow for flight.\nDo you take the bird with you or leave it behind?",
        6,
        {
            {"Take the bird with you", 9},
            {"Leave the bird behind", 7}
        }
    },
    {
        // Scene 7: Encounter the Horse
        "You continue your journey and soon meet a limping mechanical horse. Its uneven gait was caused from a dent that prevented it from running free.\nWhat do you do?",
        7,
        {
            {"Help the horse", 10},
            {"Ignore the horse and move on", 11}
        }
    },
    {
        // Scene 8: Accept Rusty's Fate
        "You accept that Rusty cannot be saved. Time passes, and he eventually stops moving. The weight of his loss stays with you, and you wonder if you should have done more.",
        8,
        {{"Try Again?",0}}
    },
    {
        // Scene 9: Continue with the Bird
        "You and the bird continue your journey together. The bird chirps with joy, even though it was still learning to fly. As you approach the creator's workshop, you notice a limping horse.\nDo you help the horse?",
        10,
        {
            {"Yes, help the horse", 19},
            {"No, continue to the creator", 11}
        }
    },
    {
        // Scene 10: Helping the Horse
        "You reinforced and greesed the horse's leg, helping it run smoothly once again. Grateful, it nudges you with its metallic head.\nDo you bring the horse along?",
        10,
        {
            {"Yes, take the horse with you", 11},
            {"No, leave the horse behind", 11}
        }
    },
    {
        // Scene 11: Reach the Creator -- no animals
        "You arrive at the creator's workshop. The creator, a disheveled figure, examines Rusty and listens to your story.\nWhat do you do?",
        11,
        {
            {"Ask about the creator's past and why they made these animals", 17},
            {"Focus only on saving Rusty", 18}
        }
    },
    {
        // Scene 12: Arrive with the Animals
        "You arrive at the creator's workshop, now accompanied by the bird and the horse. The creator looks impressed as they examine your companions before turning to Rusty.\nWhat do you do?",
        12,
        {
            {"Ask about the creator's past", 13},
            {"Focus on saving Rusty", 14}
        }
    },
    {
        // Scene 13: Learn About the Creator
        "The creator shares their story: They wished to stop change and the bad that comes with it. But these creatures, like Rusty, are unable to grow or learn. 'I wanted to hold on to everything, but nothing ever stays the same.'\nWhat do you do next?",
        13,
        {
            {"Accept the lesson about change", 15},
            {"Beg the creator to keep trying to save Rusty", 16}
        }
    },
    {
        // Scene 14: Focus Only on Rusty
        "The creator examines Rusty and works tirelessly, but in the end, they look at you with sad eyes. 'I'm sorry, but it's too late for him.'\nWhat do you do?",
        14,
        {
            {"Accept Rusty's fate", 15},
            {"Beg the creator to keep trying", 16}
        }
    },
    {
        // Scene 15: Accepting Change
        "You reflect on the journey. The bird that couldn't fly, the horse that limped, and now Rusty. Helping them showed you that everything has its time, and change is part of life. You hold Rusty close as his final spark fades, at peace with the knowledge that things must move forward, even if it means letting go.\n         The End",
        15,
        {}
    },
    {
        // Scene 16: Begging for Rusty
        "You beg the creator to keep trying, but they shake their head. 'There's nothing more I can do,' they say softly. 'You must let go.' And so, you realize, even machines cannot escape the cycle of life and death.\nYou walk away, carrying Rusty's still form and a heart heavy with grief.",
        16,
        {{"Try Again?",0}}
    },
    {
        // Scene 17: Learn About the Creator
        "The creator shares their story: They wish to stop change and the bad things that come with it, to freeze time by building creatures that never age. But these creatures, like Rusty, are unable to grow or learn. 'I wanted to hold on to everything, but nothing ever stays the same.'\nWhat do you do next?",
        13,
        {
            {"Beg the creator to keep trying to save Rusty", 16}
        }
    },
    {
        // Scene 18: Focus Only on Rusty
        "The creator examines Rusty and works tirelessly, but in the end, they look at you with sad eyes. 'I'm sorry, but it's too late for him.'\nWhat do you do?",
        14,
        {
            {"Accept Rusty's fate", 8},
            {"Beg the creator to keep trying", 16}
        }
    },
    {
        // Scene 19: Helping the Horse + bird
        "You reinforced and greesed the horse's leg, helping it run smoothly once again. Grateful, it nudges you with its metallic head.\nDo you bring the horse along?",
        10,
        {
            {"Yes, take the horse with you", 12},
            {"No, leave the horse behind", 11}
        }
    }
    };

void loadImageNames(){
    if (backgrounds.size()==0){
    for (int i = 0;i<17;i++){
        backgrounds.emplace_back(std::to_string(i+1)+".png");
    }}
}

std::pair<Storypoint,int> getNextStoryPoint(int curr, int choice) {
    if (choice >= 0 && choice <storyPoints[curr].choices.size()) {
        return {storyPoints[storyPoints[curr].choices[choice].next],storyPoints[curr].choices[choice].next};
    }
    // if not valid
    printf("no valid paths\n");
    return {storyPoints[curr],curr};
}

Storypoint getCurrStoryPoint(int curr) {
    return storyPoints[curr];
}
};