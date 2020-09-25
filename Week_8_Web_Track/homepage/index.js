function tool_tip() {
    let tool_tip = document.getElementsByClassName("tool-tip")[0];
    tool_tip.classList.toggle("hide");
}

let tool_tip_img = document.getElementsByClassName("tool-tip-img")[0]
tool_tip_img.setAttribute("onmouseover", "tool_tip()")
tool_tip_img.setAttribute("onmouseout", "tool_tip()")

